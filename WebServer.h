#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class WebServer {
public:
    char name;
    Request current_request;
    int time_remaining;

    WebServer(char n);
    bool is_busy() const;
    void start_request(Request r);
    void tick();
};

#endif