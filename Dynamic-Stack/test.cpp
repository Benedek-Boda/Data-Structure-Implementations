/*======================================================================
** You can use this file to test if your code is working
** properly by designing your own test case and test code.
** 
** You are allowed to modify this file as much as you would like.
** For grading, we will use our own filled version.
**======================================================================*/

#include <iostream>
#include <string>

#include "circular-queue.h"
#include "dynamic-stack.h"

using namespace std;

// Assert Macros for test cases.
#define ASSERT_TRUE(T) \
    if (!(T))          \
        return false;
#define ASSERT_FALSE(T) \
    if ((T))            \
        return false;

string get_status_str(bool status) {
    return status ? "PASSED" : "FAILED";
}

// Define the test suites (implementation below).
class DynamicStackTest {
private:
    bool test_result[10] = {0,0,0,0,0,0,0,0,0,0};
    string test_description[10] = {
        "Test1: new empty stack is valid",
        "Test2: push() an element on zero-element stacks",
        "Test3: peek() and pop() on one-element stack",
        "Test4: peek(), push(), and pop() work properly together",
        "Test5: push() too many elements should increase capacity",
        "Test6: push() keeps changing size and capacity",
        "Test7: pop() keeps changing size and capacity",
        "Test8: try to pop() too many elements, then push() a few elements",
        "Test9: lots of push() and pop(), all of them valid",
        "Test10: lots of push() and pop(), some of them invalid"
    };
    
public:
    string getTestDescription(int test_num);
    void runAllTests();
    void printReport();

    bool test1();
    bool test2();
    bool test3();
    bool test4();
    bool test5();
    bool test6();
    bool test7();
    bool test8();
    bool test9();
    bool test10();
};

class CircularQueueTest {
private:
    bool test_result[10] = {0,0,0,0,0,0,0,0,0,0};
    string test_description[10] = {
        "Test1: new empty queue is valid",
        "Test2: enqueue() an element on zero-element queues",
        "Test3: peek() and dequeue() on one-element queue",
        "Test4: peek(), enqueue(), and dequeue() work properly together",
        "Test5: enqueue() too many elements should fail",
        "Test6: enqueue() keeps changing tail",
        "Test7: dequeue() keeps changing head",
        "Test8: try to dequeue() too many elements, then enqueue() a few elements",
        "Test9: lots of enqueue() and dequeue(), all of them valid",
        "Test10: lots of enqueue() and dequeue(), some of them invalid"
    };

public:
    string getTestDescription(int test_num);
    void runAllTests();
    void printReport();

    bool test1();
    bool test2();
    bool test3();
    bool test4();
    bool test5();
    bool test6();
    bool test7();
    bool test8();
    bool test9();
    bool test10();
};


//======================================================================
//================================ MAIN ================================
//======================================================================
int main() {

    // The test suite has some tests implemented for you,
    // and place holders for where you can put your own.
    DynamicStackTest ds_test;

    // You can check the description for each test to see 
    // what we will be testing for with the following method.
    // Alternatively, you can also navigate to the line above 
    // where the test description is stored to read it.
    cout << ds_test.getTestDescription(1) << endl;

    // Tests can be run one at a time to get their result
    bool result = ds_test.test1();
    cout << "Test1: " << get_status_str(result) << endl << endl;

    // Or you can run all of the tests at once and generate a report.
    ds_test.runAllTests();
    ds_test.printReport();

    // Uncomment and use this for lab 2.2 when it is released.
    CircularQueueTest cq_test;
    cq_test.runAllTests();
    cq_test.printReport();

    return 0;
}


//======================================================================
//========================= Dynamic Stack Test =========================
//======================================================================
string DynamicStackTest::getTestDescription(int test_num) {
    if (test_num < 1 || test_num > 10) { // check range.
        return "";
    }
    return test_description[test_num-1];
}

void DynamicStackTest::runAllTests() {
    test_result[0] = test1();
    test_result[1] = test2();
    test_result[2] = test3();
    test_result[3] = test4();
    test_result[4] = test5();
    test_result[5] = test6();
    test_result[6] = test7();
    test_result[7] = test8();
    test_result[8] = test9();
    test_result[9] = test10();
}

void DynamicStackTest::printReport() {
    cout << "  DYNAMIC STACK TEST RESULTS  \n"
         << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n";
    for (int idx = 0; idx < 10; ++idx) {
        cout << test_description[idx] << "\n  " << get_status_str(test_result[idx]) << endl << endl;
    }
    cout << endl;
}

// Test 1: new empty stack is valid
bool DynamicStackTest::test1() {

    // Test set up.
    unsigned int capacity = 5;
    DynamicStack stack(capacity);

    // Check that the internal state is set correctly.
    ASSERT_TRUE(stack.size() == 0)
    ASSERT_TRUE(stack.empty())
    ASSERT_TRUE(stack.capacity_ == capacity)
    ASSERT_TRUE(stack.init_capacity_ == capacity)
    ASSERT_FALSE(stack.items_ == nullptr) 

    // Test the default constructor for the stack.
    DynamicStack default_stack;

    // Check that the internal state is set correctly.
    ASSERT_TRUE(default_stack.size() == 0)
    ASSERT_TRUE(default_stack.empty())
    ASSERT_TRUE(default_stack.capacity_ == 16)
    ASSERT_TRUE(default_stack.init_capacity_ == 16)
    ASSERT_FALSE(default_stack.items_ == nullptr)

    // Return true to signal all tests passed.
    return true;
}

// Test 2: push() an element on zero-element stacks
bool DynamicStackTest::test2() {

    // Test set up.
    unsigned int capacity = 5;
    DynamicStack stack(capacity);

    // Try to add data to the stack (returns void so no assert check for success).
    stack.push(100);

    // Check that the internal state is correct.
    ASSERT_TRUE(stack.size() == 1)
    ASSERT_TRUE(stack.capacity_ == capacity)
    ASSERT_TRUE(stack.init_capacity_ == capacity)
    ASSERT_FALSE(stack.items_ == nullptr)
    ASSERT_TRUE(stack.items_[0] == 100)

    // Return true to signal all tests passed.
    return true;
}

// Test 3: peek() and pop() on one-element stack
bool DynamicStackTest::test3() {

    // Test set up.
    unsigned int capacity = 5;
    DynamicStack stack1(capacity);
    DynamicStack stack2(capacity);

    // Check peek on an empty stack.
    ASSERT_TRUE(stack1.peek() == DynamicStack::EMPTY_STACK)

    // Try to add data to the stacks (returns void so no assert check for success).
    stack1.push(100);
    stack2.push(200);

    // Check the state of the capacities before popping.
    ASSERT_TRUE(stack1.init_capacity_ == 5 && stack1.capacity_ == 5 && !stack1.empty() && stack1.size_ == 1)
    ASSERT_TRUE(stack2.init_capacity_ == 5 && stack2.capacity_ == 5 && !stack2.empty() && stack2.size_ == 1)

    // Peek at the top element, then remove it.
    ASSERT_TRUE(stack1.peek() == 100 && stack1.pop() == 100)
    ASSERT_TRUE(stack2.peek() == 200 && stack2.pop() == 200)

    // Check the state of the capacities after popping.
    ASSERT_TRUE(stack1.init_capacity_ == 5 && stack1.capacity_ == 5 && stack1.empty() && stack1.size_ == 0)
    ASSERT_TRUE(stack2.init_capacity_ == 5 && stack2.capacity_ == 5 && stack2.empty() && stack2.size_ == 0)

    // Check that the peek on an empty stack still gives expected value.
    ASSERT_TRUE(stack2.peek() == DynamicStack::EMPTY_STACK)

    // Return true to signal all tests passed.
    return true;
}

// Test 4: peek(), push(), and pop() work properly together
bool DynamicStackTest::test4() {

    DynamicStack stack1(5);
    DynamicStack stack2(8);

    stack1.push(5);
    stack1.push(7);
    stack1.push(788);
    stack1.push(12);

    stack2.push(324);
    stack2.push(238);
    stack2.push(233);
    stack2.push(44);
    stack2.push(58);

    ASSERT_TRUE(stack1.peek() == 12);
    ASSERT_TRUE(stack1.peek() == 12);
    ASSERT_TRUE(stack1.pop() == 12);
    ASSERT_TRUE(stack1.init_capacity_ == 5 && stack1.capacity_ == 5 && stack1.size_ == 3 && !stack1.empty());
    ASSERT_TRUE(stack1.peek() == 788);
    ASSERT_TRUE(stack1.pop() == 788);
    ASSERT_TRUE(stack1.size_ == 2);
    ASSERT_TRUE(stack1.pop() == 7);
    ASSERT_TRUE(stack1.pop() == 5);
    ASSERT_TRUE(stack1.peek() == DynamicStack::EMPTY_STACK);

    ASSERT_TRUE(stack2.peek() == 58);
    ASSERT_TRUE(stack2.pop() == 58);
    ASSERT_TRUE(stack2.pop() == 44);
    ASSERT_TRUE(stack2.init_capacity_ == 8 && stack2.capacity_ == 8 && stack2.size_ == 3 && !stack2.empty());
    ASSERT_TRUE(stack2.peek() == 233);
    ASSERT_TRUE(stack2.pop() == 233);
    ASSERT_TRUE(stack2.pop() == 238);
    ASSERT_TRUE(stack2.size_ == 1);
    ASSERT_TRUE(stack2.pop() == 324);
    ASSERT_TRUE(stack2.peek() == DynamicStack::EMPTY_STACK);
    return true;
}

// Test 5: push() too many elements should increase capacity
bool DynamicStackTest::test5() {

    DynamicStack stack1;
    for (int i = 0; i < 17; i++){
        stack1.push(i);
    }
    ASSERT_TRUE(stack1.capacity_ == 32 && stack1.init_capacity_ == 16 && stack1.size_ == 17);

    for (int i = 17; i < 33; i++){
        stack1.push(i);
    }
    ASSERT_TRUE(stack1.capacity_ == 64 && stack1.init_capacity_ == 16 && stack1.size_ == 33);


    for (int i = 32; i >= 0; i--){
        ASSERT_TRUE(stack1.pop() == i);
    }

    ASSERT_TRUE(stack1.peek() == DynamicStack::EMPTY_STACK && stack1.size_ == 0);

    return true;
}

// Test 6: push() keeps changing size and capacity
bool DynamicStackTest::test6() {

    // Test set up.
    unsigned int capacity = 3;
    DynamicStack stack(capacity);

    // Push three elements onto the stack.
    for (int i = 0; i < 3; i++) {
        stack.push(i);
    }

    // Check the resulting capacity.
    ASSERT_TRUE(stack.init_capacity_ == 3 && stack.capacity_ == 3 && stack.size_ == 3)

    // Try adding more elements onto the "at capacity" stack.
    for (int i = 3; i < 6; i++) {
        stack.push(i);
    }

    // Check that the capacity has dynamically changed to the correct value.
    ASSERT_TRUE(stack.init_capacity_ == 3 && stack.capacity_ == 6 && stack.size_ == 6)

    // Add more.
    for (int i = 6; i < 9; i++) {
        stack.push(i);
    }

    // Check that new capacity.
    ASSERT_TRUE(stack.init_capacity_ == 3 && stack.capacity_ == 12 && stack.size_ == 9)

    // Return true to signal all tests passed.
    return true;
}

// Test 7: pop() keeps changing size and capacity
bool DynamicStackTest::test7() {

    DynamicStack stack1;
    for (int i = 0; i < 16; i++) {
        stack1.push(i);
    }
    ASSERT_TRUE(stack1.init_capacity_ == 16 && stack1.capacity_ == 16 && stack1.size_ == 16);

    for (int i = 15; i > 0; i--) {
        ASSERT_TRUE(stack1.pop() == i);
    }
    ASSERT_TRUE(stack1.init_capacity_ == 16 && stack1.capacity_ == 16 && stack1.size_ == 1);

    DynamicStack stack2;
    for (int i = 0; i < 128; i++){
        stack2.push(i);
    }
    ASSERT_TRUE(stack2.init_capacity_ == 16 && stack2.capacity_ == 128 && stack2.size_ == 128);

    for (int i = 127; i > 30; i--){
        ASSERT_TRUE(stack2.pop() == i);
    }
    ASSERT_TRUE(stack2.peek() == 30);
    ASSERT_TRUE(stack2.init_capacity_ == 16 && stack2.capacity_ == 64 && stack2.size_ == 31);

    for (int i = 30; i > 6; i--){
        ASSERT_TRUE(stack2.pop() == i);
    }
    ASSERT_TRUE(stack2.peek() == 6);
    ASSERT_TRUE(stack2.init_capacity_ == 16 && stack2.capacity_ == 16 && stack2.size_ == 7);

    return true;
}

// Test 8: try to pop() too many elements, then push() a few elements
bool DynamicStackTest::test8() {

    DynamicStack stack;

    for (int i = 0; i < 16; i++){
        stack.push(i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 16 && stack.size_ == 16);

    for (int i = 15; i >= 0; i--){
        ASSERT_TRUE(stack.pop() == i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 16 && stack.size_ == 0);
    ASSERT_TRUE(stack.peek() == DynamicStack::EMPTY_STACK)
    ASSERT_FALSE(stack.pop() == 0);
    ASSERT_TRUE(stack.pop() == DynamicStack::EMPTY_STACK);

    for (int i = 0; i < 6; i++){
        stack.push(i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 16 && stack.size_ == 6);
    return true;
}

// Test 9: lots of push() and pop(), all of them valid
bool DynamicStackTest::test9() {

    DynamicStack stack;
    for (int i = 0; i < 32; i++){
        stack.push(i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 32 && stack.size_ == 32);

    stack.push(88);
    ASSERT_TRUE(stack.peek() == 88);
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 64 && stack.size_ == 33);

    stack.pop();
    for (int i = 31; i > 14; i--){
        ASSERT_TRUE(stack.pop() == i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 32 && stack.size_ == 15);

    for (int i = 0; i < 32; i++){
        stack.push(i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 64 && stack.size_ == 47);
    ASSERT_TRUE(stack.peek() == 31);
    stack.push(85);
    stack.push(77);
    stack.push(59);
    stack.push(26);
    stack.push(55);
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 64 && stack.size_ == 52);
    ASSERT_TRUE(stack.peek() == 55);

    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 64 && stack.size_ == 48);
    ASSERT_TRUE(stack.peek() == 85);

    stack.pop();
    for (int i = 0; i < 33; i++){
        stack.pop();
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 32 && stack.size_ == 14);
    ASSERT_TRUE(stack.peek() == 13);

    for (int i = 13; i > 7; i--){
        ASSERT_TRUE(stack.pop() == i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 16 && stack.size_ == 8);

    for (int i = 7; i > 2; i--){
        ASSERT_TRUE(stack.pop() == i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 16 && stack.size_ == 3);
    return true;
}

// Test 10: lots of push() and pop(), some of them invalid
bool DynamicStackTest::test10() {
    DynamicStack stack;
    for (int i = 0; i < 32; i++){
        stack.push(i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 32 && stack.size_ == 32);

    stack.push(88);
    ASSERT_TRUE(stack.peek() == 88);
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 64 && stack.size_ == 33);

    stack.pop();
    for (int i = 31; i > 14; i--){
        ASSERT_TRUE(stack.pop() == i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 32 && stack.size_ == 15);

    for (int i = 0; i < 32; i++){
        stack.push(i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 64 && stack.size_ == 47);
    ASSERT_TRUE(stack.peek() == 31);
    stack.push(85);
    stack.push(77);
    stack.push(59);
    stack.push(26);
    stack.push(55);
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 64 && stack.size_ == 52);
    ASSERT_TRUE(stack.peek() == 55);

    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 64 && stack.size_ == 48);
    ASSERT_TRUE(stack.peek() == 85);

    stack.pop();
    for (int i = 0; i < 33; i++){
        stack.pop();
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 32 && stack.size_ == 14);
    ASSERT_TRUE(stack.peek() == 13);

    for (int i = 13; i > 7; i--){
        ASSERT_TRUE(stack.pop() == i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 16 && stack.size_ == 8);

    for (int i = 7; i > 2; i--){
        ASSERT_TRUE(stack.pop() == i);
    }
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 16 && stack.size_ == 3);

    stack.pop();
    stack.pop();
    stack.pop();
    ASSERT_TRUE(stack.init_capacity_ == 16 && stack.capacity_ == 16 && stack.size_ == 0);
    ASSERT_TRUE(stack.pop() == DynamicStack::EMPTY_STACK);
    ASSERT_TRUE(stack.peek() == DynamicStack::EMPTY_STACK);

    stack.push(55);
    stack.push(56);
    stack.push(57);
    stack.push(58);
    ASSERT_TRUE(stack.peek() == 58 && stack.size_ == 4);

    stack.pop();
    stack.pop();
    ASSERT_TRUE(stack.peek() == 56 && stack.size_ == 2);

    stack.pop();
    stack.pop();
    ASSERT_TRUE(stack.peek() == DynamicStack::EMPTY_STACK && stack.size_ == 0);
    stack.pop();
    ASSERT_TRUE(stack.pop() == DynamicStack::EMPTY_STACK);
    stack.push(2004);
    stack.push(8);
    stack.push(11);
    ASSERT_TRUE(stack.peek() == 11 && stack.size_ == 3);
    return true;
}


//======================================================================
//======================== Circular Queue Test =========================
//======================================================================
string CircularQueueTest::getTestDescription(int test_num) {
    if (test_num < 1 || test_num > 10) { // check range.
        return "";
    }
    return test_description[test_num-1];
}

void CircularQueueTest::runAllTests() {
    test_result[0] = test1();
    test_result[1] = test2();
    test_result[2] = test3();
    test_result[3] = test4();
    test_result[4] = test5();
    test_result[5] = test6();
    test_result[6] = test7();
    test_result[7] = test8();
    test_result[8] = test9();
    test_result[9] = test10();
}

void CircularQueueTest::printReport() {
    cout << "  CIRCULAR QUEUE TEST RESULTS  \n"
         << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n";
    for (int idx = 0; idx < 10; ++idx) {
        cout << test_description[idx] << "\n  " << get_status_str(test_result[idx]) << endl << endl;
    }
    cout << endl;
}

// Test 1: new empty queue is valid
bool CircularQueueTest::test1() {

    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue(capacity);

    // Check that the internal state is set correctly.
    ASSERT_TRUE(queue.size() == 0)
    ASSERT_TRUE(queue.empty())
    ASSERT_FALSE(queue.full())
    ASSERT_TRUE(queue.capacity_ == capacity)
    ASSERT_FALSE(queue.items_ == nullptr)
    ASSERT_TRUE(queue.head_ == 0 && queue.tail_ == 0)

    // Test the default constructor for the queue.
    CircularQueue default_queue;

    // Check that the internal state is set correctly.
    ASSERT_TRUE(default_queue.size() == 0)
    ASSERT_TRUE(default_queue.empty())
    ASSERT_FALSE(default_queue.full())
    ASSERT_TRUE(default_queue.capacity_ == 16)
    ASSERT_FALSE(default_queue.items_ == nullptr)
    ASSERT_TRUE(default_queue.head_ == 0 && default_queue.tail_ == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 2: enqueue() an element on zero-element queues
bool CircularQueueTest::test2() {
    
    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue1(capacity);
    CircularQueue queue2(capacity);

    // Try to enqueue data to the queues.
    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue2.enqueue(100))

    // Check that the internal state is correct.
    ASSERT_TRUE(queue1.size() == queue2.size() && queue1.size() == 1)
    ASSERT_FALSE(queue1.items_ == nullptr)
    ASSERT_FALSE(queue2.items_ == nullptr)
    ASSERT_TRUE(queue1.items_[queue1.head_] == 100)
    ASSERT_TRUE(queue2.items_[queue2.head_] == 100)
    ASSERT_TRUE(queue1.head_ == 0 && queue1.tail_ == 1)
    ASSERT_TRUE(queue2.head_ == 0 && queue2.tail_ == 1)

    // Return true to signal all tests passed.
    return true;
}

// Test 3: peek() and dequeue() on one-element queue
bool CircularQueueTest::test3() {

    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue1(capacity);
    CircularQueue queue2(capacity);

    // Check peek on an empty queue.
    ASSERT_TRUE(queue1.peek() == CircularQueue::EMPTY_QUEUE)

    // Add data to the queues.
    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue2.enqueue(200))

    // Peek at the top element, then remove it.
    ASSERT_TRUE(queue1.peek() == 100 && queue1.dequeue() == 100)
    ASSERT_TRUE(queue2.peek() == 200 && queue2.dequeue() == 200)

    // Check the resulting sizes of the queues.
    ASSERT_TRUE(queue1.size_ == queue2.size_ && queue1.size_ == 0)
    ASSERT_TRUE(queue1.empty() && queue2.empty())

    // Check that the peek on an empty queue still gives expected value.
    ASSERT_TRUE(queue2.peek() == CircularQueue::EMPTY_QUEUE)

    // Return true to signal all tests passed.
    return true;
}

// Test 4: peek(), enqueue(), and dequeue() work properly together
bool CircularQueueTest::test4() {
    CircularQueue queue1(5);
    CircularQueue queue2(8);

    queue1.enqueue(5);
    queue1.enqueue(7);
    queue1.enqueue(788);
    queue1.enqueue(12);

    queue2.enqueue(324);
    queue2.enqueue(238);
    queue2.enqueue(233);
    queue2.enqueue(44);
    queue2.enqueue(58);

    ASSERT_TRUE(queue1.peek() == 5);
    ASSERT_TRUE(queue1.peek() == 5);
    ASSERT_TRUE(queue1.dequeue() == 5);
    ASSERT_TRUE(queue1.items_[queue1.head_] == 7);
    ASSERT_TRUE(queue1.head_ == 1 && queue1.tail_ == 4);
    ASSERT_TRUE(queue1.capacity_ == 5 && queue1.capacity_ == 5 && queue1.size_ == 3 && !queue1.empty());
    ASSERT_TRUE(queue1.peek() == 7);
    ASSERT_TRUE(queue1.dequeue() == 7);
    ASSERT_TRUE(queue1.size_ == 2);
    ASSERT_TRUE(queue1.dequeue() == 788);
    ASSERT_TRUE(queue1.items_[queue1.head_] == 12)
    ASSERT_TRUE(queue1.head_ == 3 && queue1.tail_ == 4)
    ASSERT_TRUE(queue1.dequeue() == 12);
    ASSERT_TRUE(queue1.peek() == CircularQueue::EMPTY_QUEUE);

    ASSERT_TRUE(queue2.peek() == 324);
    ASSERT_TRUE(queue2.dequeue() == 324);
    ASSERT_TRUE(queue2.items_[queue2.head_] == 238);
    ASSERT_TRUE(queue2.head_ == 1 && queue2.tail_ == 5);
    ASSERT_TRUE(queue2.dequeue() == 238);
    ASSERT_TRUE(queue2.capacity_ == 8 && queue2.capacity_ == 8 && queue2.size_ == 3 && !queue2.empty());
    ASSERT_TRUE(queue2.peek() == 233);
    ASSERT_TRUE(queue2.dequeue() == 233);
    ASSERT_TRUE(queue2.items_[queue2.head_] == 44);
    ASSERT_TRUE(queue2.head_ == 3 && queue2.tail_ == 5);
    ASSERT_TRUE(queue2.dequeue() == 44);
    ASSERT_TRUE(queue2.size_ == 1);
    ASSERT_TRUE(queue2.dequeue() == 58);
    ASSERT_TRUE(queue2.peek() == CircularQueue::EMPTY_QUEUE);
    return true;
}

// Test 5: enqueue() too many elements should fail
bool CircularQueueTest::test5() {

    CircularQueue default_queue1;
    CircularQueue default_queue2;

    for (int i = 0; i < 15; i++){
        ASSERT_TRUE(default_queue1.enqueue(i) == true);
        ASSERT_TRUE(default_queue1.items_[default_queue1.head_] == 0);
        ASSERT_TRUE(default_queue1.head_ == 0 && default_queue1.tail_ == i+1);
    }

    ASSERT_TRUE(default_queue1.enqueue(15) == true);
    ASSERT_TRUE(default_queue1.head_ == 0 && default_queue1.tail_ == 0);
    ASSERT_TRUE(default_queue1.enqueue(3) == false);
    ASSERT_TRUE(default_queue1.full() == true);
    ASSERT_TRUE(default_queue1.size() == 16);

    for (int i = 0; i < 14; i++){
        ASSERT_TRUE(default_queue2.enqueue(i) == true);
        ASSERT_TRUE(default_queue2.items_[default_queue2.head_] == 0);
        ASSERT_TRUE(default_queue2.head_ == 0 && default_queue2.tail_ == i + 1);
    }
    ASSERT_TRUE(default_queue2.enqueue(14) == true);
    ASSERT_TRUE(default_queue2.full() == false);
    ASSERT_TRUE(default_queue2.enqueue(15) == true);
    ASSERT_TRUE(default_queue2.enqueue(16) == false);
    ASSERT_TRUE(default_queue2.full() == true);
    ASSERT_TRUE(default_queue2.size() == 16);

    return true;
}

// Test 6: enqueue() keeps changing tail
bool CircularQueueTest::test6() {

    CircularQueue default_queue1;

    for (int i = 0; i < 15; i++){
        ASSERT_TRUE(default_queue1.enqueue(i) == true);
        ASSERT_TRUE(default_queue1.items_[default_queue1.head_] == 0);
        ASSERT_TRUE(default_queue1.head_ == 0 && default_queue1.tail_ == i+1);
    }
    ASSERT_TRUE(default_queue1.enqueue(15) == true);
    ASSERT_TRUE(default_queue1.head_ == 0 && default_queue1.tail_ == 0);
    ASSERT_TRUE(default_queue1.dequeue() == 0);
    ASSERT_TRUE(default_queue1.dequeue() == 1);
    ASSERT_TRUE(default_queue1.dequeue() == 2);
    ASSERT_TRUE(default_queue1.size_ == 13 && default_queue1.tail_ == 0 && default_queue1.head_ == 3);

    ASSERT_TRUE(default_queue1.enqueue(0) == true);
    ASSERT_TRUE(default_queue1.tail_ == 1);
    ASSERT_TRUE(default_queue1.peek() == 3);
    ASSERT_TRUE(default_queue1.enqueue(1) == true);
    ASSERT_TRUE(default_queue1.enqueue(2) == true);

    ASSERT_TRUE(default_queue1.size_ == 16 && default_queue1.tail_ == 3 && default_queue1.head_ == 3);

    return true;
}

// Test 7: dequeue() keeps changing head
bool CircularQueueTest::test7() {

    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue(capacity);

    // Add some data.
    for (unsigned int i = 0; i < capacity; i++) {
        ASSERT_TRUE(queue.enqueue(i))
    }

    // Check that the head holds the correct item, then remove it. 
    // Check that the size reflects the change made.
    for (unsigned int i = 0; i < capacity; i++) {
        ASSERT_TRUE(queue.items_[queue.head_] == i && queue.dequeue() == i)
        ASSERT_TRUE(queue.size_ == (capacity - i - 1))
    }

    // Return true to signal all tests passed.
    return true;
}

// Test 8: try to dequeue() too many elements, then enqueue() a few elements
bool CircularQueueTest::test8() {

    CircularQueue queue1(5);

    ASSERT_TRUE(queue1.enqueue(0) == true);
    ASSERT_TRUE(queue1.enqueue(1) == true);
    ASSERT_TRUE(queue1.enqueue(3) == true);
    ASSERT_TRUE(queue1.size_ == 3 && queue1.tail_ == 3 && queue1.head_ == 0 && queue1.capacity_ == 5);

    ASSERT_TRUE(queue1.dequeue() == 0);
    ASSERT_TRUE(queue1.dequeue() == 1);
    ASSERT_TRUE(queue1.size_ == 1 && queue1.tail_ == 3 && queue1.head_ == 2 && queue1.capacity_ == 5);
    ASSERT_TRUE(queue1.dequeue() == 3);
    ASSERT_TRUE(queue1.empty() == true);
    ASSERT_TRUE(queue1.dequeue() == CircularQueue::EMPTY_QUEUE);
    ASSERT_TRUE(queue1.dequeue() == CircularQueue::EMPTY_QUEUE);
    ASSERT_TRUE(queue1.dequeue() == CircularQueue::EMPTY_QUEUE);

    ASSERT_TRUE(queue1.enqueue(0) == true);
    ASSERT_TRUE(queue1.enqueue(1) == true);
    ASSERT_TRUE(queue1.size_ == 2 && queue1.tail_ == 0 && queue1.head_ == 3 && queue1.capacity_ == 5);

    return true;
}

// Test 9: lots of enqueue() and dequeue(), all of them valid
bool CircularQueueTest::test9() {

    CircularQueue queue1(52);

    for (int i = 0; i < 32; i++){
        ASSERT_TRUE(queue1.enqueue(i) == true);
    }
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 32 && queue1.tail_ == 32 && queue1.head_ == 0);

    for (int i =0; i < 15; i++){
        ASSERT_TRUE(queue1.dequeue() == i);
    }
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 17 && queue1.tail_ == 32 && queue1.head_ == 15);

    for (int i = 32; i < 62; i++){
        ASSERT_TRUE(queue1.enqueue(i) == true);
    }
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 47 && queue1.tail_ == 10 && queue1.head_ == 15);

    ASSERT_TRUE(queue1.enqueue(62) == true);
    ASSERT_TRUE(queue1.enqueue(63) == true);
    ASSERT_TRUE(queue1.enqueue(64) == true);
    ASSERT_TRUE(queue1.enqueue(65) == true);
    ASSERT_TRUE(queue1.enqueue(66) == true);
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 52 && queue1.tail_ == 15 && queue1.head_ == 15);


    ASSERT_TRUE(queue1.dequeue() == 15);
    ASSERT_TRUE(queue1.dequeue() == 16);
    ASSERT_TRUE(queue1.dequeue() == 17);
    ASSERT_TRUE(queue1.dequeue() == 18);
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 48 && queue1.tail_ == 15 && queue1.head_ == 19);
    for (int i =19; i < 66; i++){
        ASSERT_TRUE(queue1.dequeue() == i);
    }
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 1 && queue1.tail_ == 15 && queue1.head_ == 14);
    ASSERT_TRUE(queue1.dequeue() == 66);
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 0 && queue1.tail_ == 15 && queue1.head_ == 15);

    return true;
}

// Test 10: lots of enqueue() and dequeue(), some of them invalid
bool CircularQueueTest::test10() {

    CircularQueue queue1(52);

    for (int i = 0; i < 32; i++){
        ASSERT_TRUE(queue1.enqueue(i) == true);
    }
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 32 && queue1.tail_ == 32 && queue1.head_ == 0);

    for (int i =0; i < 15; i++){
        ASSERT_TRUE(queue1.dequeue() == i);
    }
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 17 && queue1.tail_ == 32 && queue1.head_ == 15);

    for (int i = 32; i < 62; i++){
        ASSERT_TRUE(queue1.enqueue(i) == true);
    }
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 47 && queue1.tail_ == 10 && queue1.head_ == 15);

    ASSERT_TRUE(queue1.enqueue(62) == true);
    ASSERT_TRUE(queue1.enqueue(63) == true);
    ASSERT_TRUE(queue1.enqueue(64) == true);
    ASSERT_TRUE(queue1.enqueue(65) == true);
    ASSERT_TRUE(queue1.enqueue(66) == true);
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 52 && queue1.tail_ == 15 && queue1.head_ == 15);


    ASSERT_TRUE(queue1.dequeue() == 15);
    ASSERT_TRUE(queue1.dequeue() == 16);
    ASSERT_TRUE(queue1.dequeue() == 17);
    ASSERT_TRUE(queue1.dequeue() == 18);
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 48 && queue1.tail_ == 15 && queue1.head_ == 19);
    for (int i =19; i < 66; i++){
        ASSERT_TRUE(queue1.dequeue() == i);
    }
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 1 && queue1.tail_ == 15 && queue1.head_ == 14);
    ASSERT_TRUE(queue1.dequeue() == 66);
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 0 && queue1.tail_ == 15 && queue1.head_ == 15);

    for (int i = 15; i < 67; i++){
        ASSERT_TRUE(queue1.enqueue(i) == true);
    }
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 52 && queue1.tail_ == 15 && queue1.head_ == 15);
    ASSERT_TRUE(queue1.full() == true);

    for (int i = 15; i < 67; i++){
        ASSERT_TRUE(queue1.enqueue(i) == false);
    }
    ASSERT_TRUE(queue1.enqueue(55) == false);
    ASSERT_TRUE(queue1.enqueue(558) == false);
    ASSERT_TRUE(queue1.enqueue(20040811) == false);
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 52 && queue1.tail_ == 15 && queue1.head_ == 15);

    for (int i =15; i < 65; i++){
        ASSERT_TRUE(queue1.dequeue() == i);
    }
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 2 && queue1.tail_ == 15 && queue1.head_ == 13);

    ASSERT_TRUE(queue1.dequeue() == 65);
    ASSERT_TRUE(queue1.dequeue() == 66);
    ASSERT_TRUE(queue1.capacity_ == 52 && queue1.size_ == 0 && queue1.tail_ == 15 && queue1.head_ == 15);
    ASSERT_TRUE(queue1.peek() == CircularQueue::EMPTY_QUEUE)
    ASSERT_TRUE(queue1.dequeue() == CircularQueue::EMPTY_QUEUE);
    ASSERT_TRUE(queue1.dequeue() == CircularQueue::EMPTY_QUEUE);
    ASSERT_TRUE(queue1.dequeue() == CircularQueue::EMPTY_QUEUE);

    return true;
}
