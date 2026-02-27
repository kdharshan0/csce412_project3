/**
 * @file LoadBalancer.cpp
 * @brief Implementation of the LoadBalancer class logic.
 */

#include "LoadBalancer.h"
#include <iostream>
#include <sstream>
#include <vector>

#define YELLOW "\033[33m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

/**
 * @brief Helper function to convert a string IP address to a numeric long.
 * @param ip The string representation of the IP (e.g., "192.168.1.1").
 * @return The unsigned long representation of the IP.
 */
unsigned long LoadBalancer::ipToLong(std::string ip) {
    unsigned int a, b, c, d;
    char dot;
    std::stringstream ss(ip);
    ss >> a >> dot >> b >> dot >> c >> dot >> d;
    return (a << 24) + (b << 16) + (c << 8) + d;
}

/**
 * @brief Constructor for the Load Balancer.
 * Sets up initial servers and the firewall range.
 */
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

/**
 * @brief Logic for adding a request and firewall check.
 * Logs blocked requests in red.
 */
void LoadBalancer::add_request(Request r) {
    total_requests_received++;
    unsigned long incoming_ip = ipToLong(r.ip_in);

    if (incoming_ip >= range_start && incoming_ip <= range_end) {
        std::cout << RED << "[FIREWALL] Blocked Range IP: " << r.ip_in << RESET << std::endl;
        rejected_requests++;
        return;
    }
    request_queue.push(r);
}

void LoadBalancer::add_server() {
    servers.push_back(new WebServer('A' + servers.size()));
    std::cout << YELLOW <<  "Adding server.   Total: " << servers.size() << RESET << std::endl;
}

void LoadBalancer::remove_server() {
    if (servers.size() > 1) {
        delete servers.back();
        servers.pop_back();
        std::cout << YELLOW << "Removing server. Total: " << servers.size() << RESET << std::endl;
    }
}   

/**
 * @brief Dynamic scaling logic.
 * Checks queue thresholds and manages the n-cycle cooldown.
 */
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

/**
 * @brief Generates the final simulation report.
 */
void LoadBalancer::print_summary(int total_cycles) {
    int active = 0;
    for (auto s : servers) if (s->is_busy()) active++;

    std::cout << "\n" << BOLD << "Simulation Summary" << RESET << "\n";
    std::cout << "Cycles Run:         " << total_cycles << "\n";
    std::cout << "Total Requests:     " << total_requests_received << "\n";
    std::cout << "Blocked Requests:   " << RED << rejected_requests << RESET << "\n";
    std::cout << "Queue Remaining:    " << request_queue.size() << "\n";
    std::cout << "Final Server Count: " << servers.size() << "\n";
    std::cout << "Active Servers:     " << GREEN << active << RESET "\n";
    std::cout << "Idle Servers:       " << (servers.size() - active) << "\n";
}