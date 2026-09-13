#pragma once

#include <optional>
using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value)
            : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList()
        : head(nullptr), tail(nullptr) {}

    // add a new node to the front of the list
    void pushFront(const T& data) {
        Node* node = new Node(data); 
        node->prev = nullptr; // set the prev pointer of the new node to null
        if (head) { // if the List is not empty
            node->next = head; // set the next pointer of the new node to point at the original head
            head->prev = node; // set the prev pointer of the original head to point at the new node
            head = node; // reset the head pointer to point at the new node
        } else { // the List is empty
            head = node; // set the head pointer to point at the new node
            tail = node; // set the tail pointer to point at the new node as well
        }
    }

    // add a new node to the back of the list
    void pushBack(const T& data) {
        Node* node = new Node(data);
        node->prev = tail; // set the prev pointer of the new node to point at the original tail
        if (tail) { // if the list is not empty
            tail->next = node; // set the next pointer of the tail pointer to point at the new node
            tail = node;
        } else { // the list is empty
            head = node; // set the head pointer to point at the new node
            tail = node; // set the tail pointer to point at the new node as well
        }
    }

    // return and remove the first element in the list. 
    optional<T> popFront() {
        if (!head) return nullopt; // no point to return anything if the list is empty
        T value = head->data; 
        Node* tmp = head;
        head = head->next;
        if (head) { // if there was more than one node left in the list
            head->prev = nullptr; // then the prev pointer of the new head should be null.
        } else {
            tail = nullptr; // then the list is emptied.
        }
    
        delete tmp; // it's a good manner to clean up. 
        return value;
    }

    // return and remove the last element in the list. 
    optional<T> popBack() {
        if (!tail) return nullopt; // no point to return anything if the list is empty
        T value = head->data; 
        T value = tail->data;
        Node* tmp = tail;
        tail = tail->prev;
        if (tail) { // if there was more than one node left in the list
            tail->next = nullptr; // set the next pointer of the new tail to null
        } else {
            head = nullptr; // empty the whole list. 
        }
        delete tmp; // I just like cleaning this up. 
        return value;
    }

    // return the first element in the list. 
    optional<T> peekFront() const {
        if (!head) return nullopt;
        return head->data;
    }

    // return the last element in the list. 
    optional<T> peekBack() const {
        if (!tail) return nullopt;
        return tail->data;
    }

    // check if the list is empty.
    bool isEmpty() const {
        return !head;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};
