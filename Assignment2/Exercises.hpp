#include "Queue.hpp"
#include "Stack.hpp"

// Exercise 3
template <typename T>
void reverseStack(Stack<T>& stack) {
    Queue<T> queue;
    while(!stack.isEmpty()) { // copy from stack to queue (order reversed)
        auto value = stack.pop();
        queue.enqueue(value.value());
    }
    while(!queue.isEmpty()) { // copy from stack to queue (order unchanged)
        auto value = queue.dequeue();
        stack.push(value.value());
    }
} 

// Exercise 5
template <typename T>
Stack<T> copyStack(Stack<T>& stack) {
    Queue<T> queue;
    Stack<T> result;
    while(!stack.isEmpty()) {
        auto value = stack.pop();
        queue.enqueue(value.value());
    }
    while(!queue.isEmpty()) {
        auto value = queue.dequeue();
        stack.push(value.value());
    }
    while(!stack.isEmpty()) {
        auto value = stack.pop();
        result.push(value.value());
        queue.enqueue(value.value());
    }
    while(!queue.isEmpty()) {
        auto value = queue.dequeue();
        stack.push(value.value());
    }
    return result;
}