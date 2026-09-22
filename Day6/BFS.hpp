#pragma once

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "DFS.hpp"

using namespace std;

template <typename T>
Node<T>* bfs(Node<T>* root, T target) {
    unordered_set<Node<T>*> visited;
    queue<Node<T>*> toVisit;
    
    visited.insert(root);
    toVisit.push(root);


    while(!toVisit.empty()) {
        Node<T>* cur = toVisit.front();
        toVisit.pop();
        if (cur->data == target) {
            return cur;
        }
        for (const auto& child : cur->children) {
            if (!visited.count(child)) {
                visited.insert(child);
                toVisit.push(child);
            }
        }
    }
    return nullptr;
}