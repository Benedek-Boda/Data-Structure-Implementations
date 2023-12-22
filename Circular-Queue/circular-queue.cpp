#include "circular-queue.h"
#include <iostream>
const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue() {
    size_ = 0;
    capacity_ = 16;
    head_ = 0;
    tail_ = 0;
    items_ = new QueueItem[capacity_];
}

CircularQueue::CircularQueue(unsigned int capacity) {
    size_ = 0;
    capacity_ = capacity;
    head_ = 0;
    tail_ = 0;
    items_ = new QueueItem[capacity_];
}

CircularQueue::~CircularQueue() {
    delete [] items_;
    items_ = nullptr;
}

unsigned int CircularQueue::size() const {
    return size_;
}

bool CircularQueue::empty() const {
    if (size_ == 0){
        return true;
    }
    return false;
}

bool CircularQueue::full() const {
    if (size_ == capacity_){
        return true;
    } else return false;
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if (empty()){
        return EMPTY_QUEUE;
    }
    else return items_[head_];
}

bool CircularQueue::enqueue(QueueItem value) {
   if (full()){
       return false;
   } else {
       items_[tail_] = value;
       size_++;
       if (tail_ == capacity_ - 1){
           tail_ = 0;
       } else tail_++;
       return true;
   }
}

CircularQueue::QueueItem CircularQueue::dequeue() {
    if (empty()){
        return EMPTY_QUEUE;
    } else {
        QueueItem dequeueditem = items_[head_];
        size_--;
        if (head_ == capacity_ -1){
            head_ = 0;
        } else head_++;

        return dequeueditem;
    }
}

void CircularQueue::print() const {
    for (int i = 0; i < size_; i++){
        std::cout << items_[i] << std:: endl;
    }
}
