#include "LoadBalancer.h"
#include <iostream>
#include <sstream>
#include <vector>

unsigned long LoadBalancer::ipToLong(std::string ip) {
    unsigned int a, b, c, d;
    char dot;
    std::stringstream ss(ip);
    ss >> a >> dot >> b >> dot >> c >> dot >> d;
    return (a << 24) + (b << 16) + (c << 8) + d;
}

LoadBalancer::LoadBalancer(int num_servers, std::string start_ip, std::string end_ip) 
    : system_time(0), cooldown_remaining(0), cooldown_period(num_servers), total_requests_received(0), rejected_requests(0) {
    range_start = ipToLong(start_ip);
    range_end = ipToLong(end_ip);
    
    for (int i = 0; i < num_servers; ++i) {
        servers.push_back(new WebServer('A' + i));
    }
}

LoadBalancer::~LoadBalancer() {
    for (auto s : servers) delete s;
}

void LoadBalancer::add_request(Request r) {
    total_requests_received++;
    unsigned long incoming_ip = ipToLong(r.ip_in);

    if (incoming_ip >= range_start && incoming_ip <= range_end) {
        std::cout << "[FIREWALL] Blocked Range IP: " << r.ip_in << std::endl;
        rejected_requests++;
        return;
    }
    request_queue.push(r);
}

void LoadBalancer::add_server() {
    servers.push_back(new WebServer('A' + servers.size()));
    std::cout  << "Adding server.   Total: " << servers.size() << std::endl;
}

void LoadBalancer::remove_server() {
    if (servers.size() > 1) {
        delete servers.back();
        servers.pop_back();
        std::cout << "Removing server. Total: " << servers.size() << std::endl;
    }
}   

void LoadBalancer::balance_check() {
    if (cooldown_remaining > 0) {
        cooldown_remaining--;
        return;
    }

    size_t s_count = servers.size();
    size_t q_size = request_queue.size();

    if (q_size > 80 * s_count) {
        add_server();
        cooldown_period += 1;
        cooldown_remaining = cooldown_period;
    } 
    else if (q_size < 50 * s_count && s_count > 1) {
        remove_server();
        cooldown_period -= 1;
        cooldown_remaining = cooldown_period;
    }
}

void LoadBalancer::print_summary(int total_cycles) {
    int active = 0;
    for (auto s : servers) if (s->is_busy()) active++;

    std::cout << "\n" << "Simulation Summary" << "\n";
    std::cout << "Cycles Run:         " << total_cycles << "\n";
    std::cout << "Total Requests:     " << total_requests_received << "\n";
    std::cout << "Blocked Requests:   " << rejected_requests << "\n";
    std::cout << "Queue Remaining:    " << request_queue.size() << "\n";
    std::cout << "Final Server Count: " << servers.size() << "\n";
    std::cout << "Active Servers:     " << active << "\n";
    std::cout << "Idle Servers:       " << (servers.size() - active) << "\n";
}