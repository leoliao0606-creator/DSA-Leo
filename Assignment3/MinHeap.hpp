#include <vector>
#include <utility>
#include <optional>

using namespace std;

template <typename T>
class MinHeap {
private:
    vector<pair<T, double>> heap;
public:
    /**
     * @return true if the heap is empty, false otherwise
     */
    bool empty() {
        return heap.empty();
    }

    /**
     * Add [elem] with at level [priority]
     */
    void addWithPriority(T elem, double priority) {
        heap.push_back({elem, priority});
        int idx = heap.size() - 1;
        while(idx > 0 && heap[(idx-1)/2].second > priority) {
            swap(heap[idx], heap[(idx-1)/2]);
            idx = (idx-1)/2;
        }
    }

    /**
     * Get the next (highest priority) element and remove this element from the queue.
     * @return the next element in terms of priority.  If empty, return null.
     */
    optional<T> next() {
        if (heap.empty()) return nullopt;
        T next = heap.front().first;
        swap(heap[0], heap[heap.size()-1]);
        heap.erase(heap.begin() + heap.size() - 1);
        int idx = 0;
        while(idx < heap.size()-1) {
            if (2*idx+1 < heap.size()) {
                if (2*idx+2 < heap.size()) {
                    if (heap[idx].second > heap[2*idx+1].second || heap[idx].second > heap[2*idx+2].second) {
                        if (heap[2*idx+1].second <= heap[2*idx+2].second) {
                            swap(heap[idx], heap[2*idx+1]);
                            idx = 2*idx+1;
                        } else {
                            swap(heap[idx], heap[2*idx+2]);
                            idx = 2*idx+2;
                        }
                    } else {
                        break;
                    }
                } else if (heap[idx].second > heap[2*idx+1].second) {
                    swap(heap[idx], heap[2*idx+1]);
                    idx = 2*idx+1;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        return next;
    }
};