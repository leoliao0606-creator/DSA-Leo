#include <vector>
#include <utility>
#include <optional>
using namespace std;

template <typename T>
class MinPriorityQueue {
private:
    vector<pair<T, double>> pq;
public:
    /**
     * @return true if the queue is empty, false otherwise
     */
    bool empty() {
        return pq.empty();
    }

    /**
     * Add [elem] with at level [priority]
     */
    void addWithPriority(T elem, double priority) {
        for (int i=0; i<pq.size(); i++) {
            if (priority < pq[i].second) {
                pq.insert(pq.begin() + i, {elem, priority});
                return;
            }
        }
        pq.push_back({elem, priority});
    }

    /**
     * Get the next (highest priority) element and remove this element from the queue.
     * @return the next element in terms of priority.  If empty, return null.
     */
    optional<T> next() {
        if (pq.empty()) return nullopt;
        T next = pq.front().first;
        pq.erase(pq.begin());
        return next;
    }

    /**
     * Adjust the priority of the given element
     * @param elem whose priority should change
     * @param newPriority the priority to use for the element
     *   the lower the priority the earlier the element int
     *   the order.
     */
    void adjustPriority(T elem, double newPriority) {
        if (pq.empty()) return;
        for (int i=0; i<pq.size(); i++) {
            if (pq[i].first == elem) {
                pq.erase(pq.begin() + i);
                break;
            }
        }
        addWithPriority(elem, newPriority);
    }
};