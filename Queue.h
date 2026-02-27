#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include "Request.h"

class RequestQueue {
public:
    std::queue<Request> q;
    void push(const Request& r) { q.push(r); }
    void pop() { q.pop(); }
    Request& front() { return q.front(); }
    bool empty() const { return q.empty(); }
    size_t size() const { return q.size(); }
};

#endif