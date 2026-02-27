/**
 * @file Queue.h
 * @brief Simple wrapper for the STL queue to manage Request objects.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include "Request.h"

/**
 * @class RequestQueue
 * @brief A container class that manages a queue of Request objects.
 * * This class provides a simplified interface for adding, removing, 
 * and accessing web requests during the simulation.
 */
class RequestQueue {
public:
    /** @brief The underlying STL queue holding Request objects. */
    std::queue<Request> q;

    /**
     * @brief Adds a new request to the back of the queue.
     * @param r The Request object to be queued.
     */
    void push(const Request& r) { q.push(r); }

    /**
     * @brief Removes the request at the front of the queue.
     */
    void pop() { q.pop(); }

    /**
     * @brief Accesses the request at the front of the queue.
     * @return A reference to the front Request object.
     */
    Request& front() { return q.front(); }

    /**
     * @brief Checks if the queue has no requests.
     * @return True if empty, false otherwise.
     */
    bool empty() const { return q.empty(); }

    /**
     * @brief Gets the current number of requests in the queue.
     * @return The size of the queue as a size_t.
     */
    size_t size() const { return q.size(); }
};

#endif