#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <string>
#include "WebServer.h"
#include "Queue.h"

class LoadBalancer {
private:
    int cooldown_remaining;
    int cooldown_period;
    unsigned long range_start;
    unsigned long range_end;
    int total_requests_received;
    int rejected_requests;

    unsigned long ipToLong(std::string ip);

public:
    int system_time;
    RequestQueue request_queue;
    std::vector<WebServer*> servers;

    LoadBalancer(int start_servers, std::string start_ip, std::string end_ip);
    ~LoadBalancer();

    void add_request(Request r);
    void add_server();
    void remove_server();
    void balance_check();
    void print_summary(int total_cycles);
};

#endif