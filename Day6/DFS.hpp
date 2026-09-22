#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

using namespace std;

template <typename T>
struct Node {
        T data;
        vector<Node*> children;

        Node(const T& value) : data(value) {}
};

template <typename T>
Node<T>* dfs(Node<T>* root, T target) {
    unordered_set<Node<T>*> toVisit;
    stack<Node<T>*> priorityList;
    
    toVisit.insert(root);
    priorityList.push(root);

    while(!priorityList.empty()) {
        Node<T>* cur = priorityList.top();
        priorityList.pop();
        if (cur->data == target) {
            return cur;
        }
        for (int i = cur->children.size() - 1; i >=0; i--) {
            Node<T>* child = cur->children[i];
            if (!toVisit.count(child)) {
                toVisit.insert(child);
                priorityList.push(child);
            }
        }
    } 
    return nullptr;
}