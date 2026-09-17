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
    while(!stack.isEmpty()) { // copty from original stack to queue (order reversed)
        auto value = stack.pop();
        queue.enqueue(value.value());
    }
    while(!queue.isEmpty()) { // copy from queue to the original stack (order unchanged)
        auto value = queue.dequeue();
        stack.push(value.value());
    }
    while(!stack.isEmpty()) { // copy from original stack to both queue (order reversed) and new stack (order reversed)
        auto value = stack.pop();
        result.push(value.value());
        queue.enqueue(value.value());
    }
    /*
    This reason why I have an extra loop here is that we didn't implemented the deep copy function for stack,
    which is an unique feature in C++, while passing parameters by value requires deep copy to avoid conflits, 
    so I can only set the paramenter of the current function to be pass by reference. This means that if I 
    make any change to the parameter pass in, the same variable where it's passed in a function call will also
    be modified. Hence I have to restore the stack to it's original state before returning. 
    */ 
    while(!queue.isEmpty()) { // copy from queue to original stack (order unchanged)
        auto value = queue.dequeue();
        stack.push(value.value());
    }
    return result;
}