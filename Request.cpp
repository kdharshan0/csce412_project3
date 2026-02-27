/**
 * @file Request.cpp
 * @brief Implementation of random request generation.
 */
#include "Request.h"

/**
 * @brief Initializes a Request with random IP addresses, time, and job type.
 * Uses a lambda function for IP string generation.
 */
Request::Request() {
    auto gen_ip = []() {
        return std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." +
               std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
    };

    ip_in = gen_ip();
    ip_out = gen_ip();
    time = rand() % 50 + 1; // limits clock cycles from 1-50
}