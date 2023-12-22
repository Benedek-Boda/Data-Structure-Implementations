#include "dynamic-stack.h"
#include <iostream>

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack() {
    size_ = 0;
    init_capacity_ = 16;
    capacity_ = init_capacity_;
    items_ = new StackItem[capacity_];
}

DynamicStack::DynamicStack(unsigned int capacity){
    size_ = 0;
    init_capacity_ = capacity;
    capacity_ = capacity;
    items_ = new StackItem[capacity_];
}

DynamicStack::~DynamicStack() {
    delete [] items_;
    items_ = nullptr;
}

unsigned int DynamicStack::size() const {
    return size_;
}

bool DynamicStack::empty() const {
    if (size_ == 0){
        return true;
    }
    return false;
}

DynamicStack::StackItem DynamicStack::peek() const {
    if (empty()){
        return EMPTY_STACK;
    }
    else return items_[size_ - 1];
}

void DynamicStack::push(StackItem value) {
    if (size_ == capacity_){
        StackItem *newarray = new StackItem[capacity_ + capacity_];
        capacity_ = capacity_ + capacity_;
        for (int i = 0; i < size_; i++){
            newarray[i] = items_[i];
        }
        StackItem *temp = items_;
        items_ = newarray;
        delete [] temp;
        temp = nullptr;
    }
    items_[size_] = value;
    size_++;
}

DynamicStack::StackItem DynamicStack::pop() {
    if (empty()){
        return EMPTY_STACK;
    }

    StackItem poppeditem = items_[size_-1];
    size_--;

    if (size_ <= (capacity_/4) && (capacity_/2) >= init_capacity_){
        StackItem *newarray = new StackItem[capacity_/2];
        capacity_ = capacity_/2;
        for (int i = 0; i < size_; i++){
            newarray[i] = items_[i];
        }
        StackItem *temp = items_;
        items_ = newarray;
        delete [] temp;
        temp = nullptr;
    }
    return poppeditem;
}

void DynamicStack::print() const {
    for (int j = 0; j < size_; j++){
        std::cout << items_[j]<<std::endl;
    }
}
