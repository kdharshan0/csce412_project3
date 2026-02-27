/**
 * @file WebServer.h
 * @brief Class definition for a WebServer that processes requests.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @class WebServer
 * @brief Simulates a single server that handles one Request at a time.
 */

class WebServer {
public:
    char name;          /**< Identifier for the server (e.g., '1', '2') */
    int time_remaining; /**< Cycles remaining until the current request is done */
    Request current_request; /**< The request currently being handled */

    /**
     * @brief Constructs a server with a specific identifier.
     * @param n The name/ID of the server.
     */
    WebServer(char n);

    /**
     * @brief Checks if the server is currently busy.
     * @return True if time_remaining > 0, False otherwise.
     */
    bool is_busy() const;

    /**
     * @brief Starts processing a new request.
     * @param r The Request object to process.
     */
    void start_request(Request r);

    /**
     * @brief Decrements the time_remaining by one cycle.
     */
    void tick();
};

#endif