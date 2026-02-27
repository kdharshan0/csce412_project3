#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @brief Represents a single web request with IPs and processing time.
 */

struct Request {
    std::string ip_in;
    std::string ip_out;
    int time;

    Request();
};

#endif