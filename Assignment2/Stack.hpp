#include <optional>
#include "DoublyLinkedList.hpp"
using namespace std;

template <typename T>
class Stack {
private:
    DoublyLinkedList<T> stack;

public:
    void push(const T& data) {
        stack.pushBack(data);
    }

    optional<T> pop() {
        return stack.popBack();
    }

    optional<T> peek() const {
        return stack.peekBack();
    }

    bool isEmpty() const {
        return stack.isEmpty();
    }
};