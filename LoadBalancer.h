/**
 * @file LoadBalancer.h
 * @brief Manages server allocation and request queuing.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <string>
#include "WebServer.h"
#include "Queue.h"

/**
 * @class LoadBalancer
 * @brief Handles dynamic scaling of servers and firewall management.
 */
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

    /**
     * @brief Initializes the Load Balancer with servers and firewall range.
     * @param start_servers Initial number of web servers.
     * @param start_ip Lower bound of blocked IP range.
     * @param end_ip Upper bound of blocked IP range.
     */
    LoadBalancer(int start_servers, std::string start_ip, std::string end_ip);
    ~LoadBalancer();

    /**
     * @brief Adds a request to the queue after firewall check.
     * @param r The incoming request.
     */
    void add_request(Request r);

    /**
     * @brief Allocates another server to our load balancer
     */
    void add_server();

    /**
     * @brief Removes a server
     */
    void remove_server();

    /**
     * @brief Evaluates queue size and scales servers if cooldown has passed.
     */
    void balance_check();

    /**
     * @brief Prints the final simulation metrics.
     * @param total_cycles Total number of cycles the simulation ran.
     */
    void print_summary(int total_cycles);
};

#endif