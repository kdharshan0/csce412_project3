#include <iostream>
#include <ctime>
#include "LoadBalancer.h"

int main() {
    srand(time(0));
    int num_servers, run_time;

    std::cout << "Enter number of servers: ";
    std::cin >> num_servers;
    std::cout << "Enter run time (cycles): ";
    std::cin >> run_time;   

    std::string ip_low = "192.168.1.0";
    std::string ip_high = "192.168.1.255";

    int randomness = 5;

    LoadBalancer lb(num_servers, ip_low, ip_high);

    // initialization of queue (servers * 100)
    for (int i = 0; i < num_servers * 100; ++i) {
        lb.add_request(Request());
    }

    std::cout << std::endl;
    std::cout << "Starting queue size: " << lb.request_queue.size() << std::endl;
    std::cout << "Current odds of request generation: 1 in " << randomness << std::endl;
    std::cout << std::endl;
    std::cout << "Simulation Starting..." << std::endl;

    for (int curr_cycle = 0; curr_cycle < run_time; ++curr_cycle) {
        // assign request to idle servers
        for (auto& s : lb.servers) {
            if (!s->is_busy() && !lb.request_queue.empty()) {   
                s->start_request(lb.request_queue.front());
                lb.request_queue.pop();
            }
            s->tick();
        }

        // randomly adds new requests
        if (rand() % randomness == 0) lb.request_queue.push(Request());

        lb.balance_check();
    }
    
    std::cout << "Simulation Finished!" << std::endl;
    lb.print_summary(run_time);

    return 0;
}