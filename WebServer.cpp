#include "WebServer.h"

WebServer::WebServer(char n) : name(n), time_remaining(0) {}

bool WebServer::is_busy() const { return time_remaining > 0; }

void WebServer::start_request(Request r) {
    current_request = r;
    time_remaining = r.time;
}

void WebServer::tick() {
    if (time_remaining > 0) time_remaining--;
}