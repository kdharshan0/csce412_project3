/**
 * @file main.cpp
 * @brief Driver program for the Load Balancer simulation.
 * * This file handles user configuration, initializes the Load Balancer,
 * and executes the clock cycle loop that simulates network traffic.
 */

#include <iostream>
#include <ctime>
#include "LoadBalancer.h"

/**
 * @brief Main entry point for the simulation.
 * * Reads configuration from "config.txt", seeds the random number generator,
 * and runs the simulation for the specified number of clock cycles.
 * * @return int Execution status code.
 */
int main() {
    srand(time(0));
    int num_servers, run_time;
    int randomness = 5;
    std::string ip_low = "192.168.1.0";
    std::string ip_high = "192.168.1.255";

    /**
     * @section config_load Configuration Loading
     * Attempt to load parameters via user input.
     */
    std::cout << "Enter number of servers: ";
    std::cin >> num_servers;
    std::cout << "Enter run time (cycles): ";
    std::cin >> run_time;   

    LoadBalancer lb(num_servers, ip_low, ip_high);

    /**
     * @section init_queue Initial Queue Population
     * Generate an initial full queue.
     */
    for (int i = 0; i < num_servers * 100; ++i) {
        lb.add_request(Request());
    }

    std::cout << std::endl;
    std::cout << "Starting queue size: " << lb.request_queue.size() << std::endl;
    std::cout << "Current odds of request generation: 1 in " << randomness << std::endl;
    std::cout << std::endl;
    std::cout << "Simulation Starting..." << std::endl;

    /**
     * @section sim_loop Simulation Loop
     * Processes each clock cycle, manages server tasks, and handles dynamic scaling.
     */
    for (int curr_cycle = 0; curr_cycle < run_time; ++curr_cycle) {
        // assign request to idle servers
        for (auto& s : lb.servers) {
            if (!s->is_busy() && !lb.request_queue.empty()) {   
                s->start_request(lb.request_queue.front());
                lb.request_queue.pop();
            }
            s->tick();
        }

        /**
         * @section traffic_sim Traffic Simulation
         * Randomly inject new requests into the system.
         */
        if (rand() % randomness == 0) lb.request_queue.push(Request());

        // dynamic scaling check
        lb.balance_check();
    }
    
    std::cout << "Simulation Finished!" << std::endl;
    lb.print_summary(run_time);

    return 0;
}