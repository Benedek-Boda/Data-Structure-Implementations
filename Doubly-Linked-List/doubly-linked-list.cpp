#include "doubly-linked-list.h"

DoublyLinkedList::Node::Node(DataType data) {
    value = data;
    prev = nullptr;
    next = nullptr;
}


DoublyLinkedList::DoublyLinkedList() {
    Node *newNode = new Node(CAPACITY);
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
}


DoublyLinkedList::~DoublyLinkedList() {
   Node* current = head_;
   while (current != nullptr){
       Node* next = current->next;
       delete current;
       current = next;
   }
}


unsigned int DoublyLinkedList::size() const {
    return size_;
}


unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;
}


bool DoublyLinkedList::empty() const {
    if (size_ == 0){
        return true;
    }
    else return false;
}


bool DoublyLinkedList::full() const {
    if (size_ == CAPACITY){
        return true;
    }
    else return false;
}


DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {
    Node *current = head_;
    int i = 0;
    while (i < index){
        if (current->next == nullptr){
            return current->value;
        }
        current = current->next;
        i++;
    }
    return current->value;
}


unsigned int DoublyLinkedList::search(DataType value) const {
    Node *current = head_;
    if(head_ == nullptr){
        return size_;
    }
    int i =0;
    while (current->value != value){
        current = current->next;
        i++;
        if (i >= size_){
            return size_;
        }
    }
    return i;
}


void DoublyLinkedList::print() const {
    Node *current = head_;
    int i = 0;
    while (i < size_){
        i++;
    }
}


DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const {
    if (index >= size_) {
        return nullptr;
    }

    Node* current = head_;
    for (unsigned int i = 0; i < index; i++) {
        current = current->next;
    }

    return current;
}


bool DoublyLinkedList::insert(DataType value, unsigned int index) {
    if (full() || index > size_){
        return false;
    }
    Node *newNode = new Node(value);

    if (index == 0){
        if (head_ == nullptr){
            newNode->prev = nullptr;
            head_ = newNode;
            tail_ = newNode;
            size_++;
            return true;
        }
        else{
            head_->prev = newNode;
            newNode->next = head_;
            head_ = newNode;
            size_++;
            return true;
        }
    }

    if (size_ > 0 && index == size_){
        newNode->prev = tail_;
        tail_->next = newNode;
        tail_ = newNode;
        size_++;
        return true;
    }

    Node *previous = head_;
    Node *current = head_->next;
    int i = 1;
    while(i < index){
        previous = current;
        current = current->next;
        if (current == nullptr){
            break;
        }
        i++;
    }
    newNode->next = current;
    previous->next = newNode;
    newNode->prev = previous;
    current->prev = newNode;
    size_++;
    return true;
}



bool DoublyLinkedList::insert_front(DataType value) {
    return insert(value, 0);
}


bool DoublyLinkedList::insert_back(DataType value) {
    return insert(value, size_);
}


bool DoublyLinkedList::remove(unsigned int index) {
    if (index >= size_ || size_ == 0) {
        return false;
    }

    if (index == 0) {
        return remove_front();
    }

    if (index == size_ - 1) {
        return remove_back();
    }

    Node* current = head_;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    Node* previousnode = current->prev;
    Node* nextnode = current->next;

    previousnode->next = nextnode;
    nextnode->prev = previousnode;

    delete current;
    size_--;

    return true;
}


bool DoublyLinkedList::remove_front() {
    Node* current = head_;
    if (size() == 0){
        return false;
    }
    if (size() == 1){
        head_ = nullptr;
        tail_ = nullptr;
        delete current;
    }
    else{
        head_ = current->next;
        head_->prev =nullptr;
        delete current;
    }
    size_--;
    return true;
}


bool DoublyLinkedList::remove_back() {
    Node* current = tail_;
    if (size() == 0){
        return false;
    }
    if(size() == 1){
        head_ = nullptr;
        tail_ = nullptr;
        delete current;
    }
    else{
        tail_ = current->prev;
        tail_->next = nullptr;
        delete current;
    }
    size_--;
    return true;
}


bool DoublyLinkedList::replace(unsigned int index, DataType value) {
    Node* current = head_;
    if (size_ == 0 || size_ < index){
        return false;
    }
    unsigned int i = 0;
    while(current != nullptr && i < index) {
        current = current->next;
        i++;
    }
    current->value = value;
    return true;
}


