#include <optional>
#include "DoublyLinkedList.hpp"
using namespace std;

template <typename T>
class Queue {
private:
    DoublyLinkedList<T> queue;

public:
    void enqueue(const T& data) {
        queue.pushBack(data);
    }

    optional<T> dequeue() {
        return queue.popFront();
    }

    optional<T> peek() const {
        return queue.peekFront();
    }

    bool isEmpty() const {
        return queue.isEmpty();
    }
};