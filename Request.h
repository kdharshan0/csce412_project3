/**
 * @file Request.h
 * @brief Definition of the Request struct for simulation jobs.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @struct Request
 * @brief Holds data for a network request including IPs and processing time.
 */

struct Request {
    std::string ip_in;  /**< Source IP address */
    std::string ip_out; /**< Destination IP address */
    int time;           /**< Number of clock cycles needed for processing */
    
    /**
     * @brief Constructor that initializes a request with random data.
     */
    Request();
};

#endif