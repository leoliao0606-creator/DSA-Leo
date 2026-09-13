#include <cassert>
#include <string>
#include "DoublyLinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

using namespace std;

void testDoublyLinkedList() {
    DoublyLinkedList<int> list;

    assert(list.isEmpty());
    assert(!list.peekFront());
    assert(!list.peekBack());
    assert(!list.popFront());
    assert(!list.popBack());

    list.pushFront(10);

    assert(!list.isEmpty());
    assert(list.peekFront() == 10);
    assert(list.peekBack() == 10);

    list.pushFront(5);

    assert(list.peekFront() == 5);
    assert(list.peekBack() == 10);

    list.pushBack(20);

    assert(list.peekFront() == 5);
    assert(list.peekBack() == 20);
    assert(list.popFront() == 5);
    assert(list.peekFront() == 10);
    assert(list.popBack() == 20);
    assert(list.peekBack() == 10);
    assert(list.popFront() == 10);
    assert(list.isEmpty());
    assert(!list.popFront());
    assert(!list.popBack());
}

void testDoublyLinkedListString() {
    DoublyLinkedList<string> list;

    list.pushBack("A");
    list.pushBack("B");
    list.pushFront("C");

    assert(list.peekFront() == "C");
    assert(list.peekBack() == "B");
    assert(list.popFront() == "C");
    assert(list.popBack() == "B");
    assert(list.popFront() == "A");
    assert(list.isEmpty());
}

void testStack() {
    Stack<int> stack;

    assert(stack.isEmpty());
    assert(!stack.peek());
    assert(!stack.pop());

    stack.push(10);

    assert(!stack.isEmpty());
    assert(stack.peek() == 10);

    stack.push(20);
    stack.push(30);

    assert(stack.peek() == 30);
    assert(stack.pop() == 30);
    assert(stack.peek() == 20);
    assert(stack.pop() == 20);
    assert(stack.pop() == 10);
    assert(stack.isEmpty());
    assert(!stack.pop());
}

void testQueue() {
    Queue<int> queue;

    assert(queue.isEmpty());
    assert(!queue.peek());
    assert(!queue.dequeue());

    queue.enqueue(10);

    assert(!queue.isEmpty());
    assert(queue.peek() == 10);

    queue.enqueue(20);
    queue.enqueue(30);
    assert(queue.peek() == 10);
    assert(queue.dequeue() == 10);
    assert(queue.peek() == 20);
    assert(queue.dequeue() == 20);
    assert(queue.dequeue() == 30);
    assert(queue.isEmpty());
    assert(!queue.dequeue());
}

int main() {
    testDoublyLinkedList();
    testDoublyLinkedListString();
    testStack();
    testQueue();

    return 0;
}