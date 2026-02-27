/**
 * @file WebServer.cpp
 * @brief Implementation of the WebServer processing cycles.
 */

#include "WebServer.h"

/**
 * @brief Constructor for WebServer.
 * @param n Character name for the server.
 */
WebServer::WebServer(char n) : name(n), time_remaining(0) {}

/**
 * @brief Simple busy-check based on time remaining.
 * @return bool True if the server is still processing a request.
 */
bool WebServer::is_busy() const { return time_remaining > 0; }

/**
 * @brief Loads a request into the server and sets the countdown.
 * @param r The Request object to handle.
 */
void WebServer::start_request(Request r) {
    current_request = r;
    time_remaining = r.time;
}

/**
 * @brief Simulates one clock cycle of work.
 */
void WebServer::tick() {
    if (time_remaining > 0) time_remaining--;
}