// CircularQueue implements a queue using an array as a circular track.

#ifndef CIRCULAR_QUEUE_HPP
#define CIRCULAR_QUEUE_HPP

#include "Joint.hpp"

class CircularQueue
{
public:
    // Can be seen outside as CircularQueue::QueueItem
    typedef Joint* QueueItem;
    // Used as an indicator of empty queue.
    static const QueueItem EMPTY_QUEUE;

    // Default constructor used to initialize the circular queue class.
    // Default capacity is 16.
    CircularQueue();
    CircularQueue(unsigned int capacity);

    // Destructor.
    ~CircularQueue();

    // Takes as an argument a QueueItem value. If the queue is not full, it
    // inserts the value at the rear of the queue (after the last item), and
    // returns true. It returns false if the process fails.
    bool enqueue(QueueItem value);

    // Returns the value at the front of the queue. If the queue is not empty,
    // the front item is removed from it. If the queue was empty before the
    // dequeue, the EMPTY_QUEUE constant is returned.
    QueueItem dequeue();

    // Returns the value at the front of the queue without removing it from the
    // queue. If the queue was empty before the peek, the EMPTY_QUEUE constant is
    // returned.
    QueueItem peek() const;

    // Returns true if the queue is empty and false otherwise.
    bool empty() const;

    // Returns true if the queue is full and false otherwise.
    bool full() const;

    // Returns the number of items in the queue.
    int size() const;

    // Rrints the queue items sequentially ordered from the front to the rear of
    // the queue.
    void print() const;

private:
    // Override copy constructor and assignment operator in private so we can't
    // use them.
    CircularQueue(const CircularQueue& other) {}
    CircularQueue operator=(const CircularQueue& other) {}

private:
    // As the capacity is fixed, you may as well use an array here.
    QueueItem *items_;

    // Indices for keeping track of the circular array
    int head_, tail_;
    int capacity_;
    int size_;
};

#endif
