#include "Request.h"

Request::Request() {
    auto gen_ip = []() {
        return std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." +
               std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
    };

    ip_in = gen_ip();
    ip_out = gen_ip();
    time = rand() % 50 + 1; // limits clock cycles from 1-50
}