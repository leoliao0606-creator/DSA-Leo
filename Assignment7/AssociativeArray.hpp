#pragma once
#include <functional>
#include <list>
#include <optional>
#include <utility>
#include <vector>
using namespace std;

// Hash table map: separate chaining + division method, rehashes as it grows.
template <typename K, typename V>
class AssociativeArray {
private:
    // hash table primes (planetmath.org/goodhashtableprimes)
    static constexpr size_t PRIMES[] = {
        53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
        49157, 98317, 196613, 393241, 786433, 1572869, 3145739,
        6291469, 12582917, 25165843, 50331653, 100663319,
        201326611, 402653189, 805306457, 1610612741};

    static constexpr double MAX_LOAD = 0.75;  // rehash when size / buckets goes past this

    vector<list<pair<K, V>>> buckets;
    size_t count = 0;
    size_t primeIdx = 0;  // which prime we're using for bucket count

    // division method: hash(k) mod number of buckets
    size_t indexOf(const K& k) const {
        size_t key = hash<K>{}(k);
        return key % PRIMES[primeIdx];
    }

    // move to the next prime and re-insert everything
    void rehash() {
        vector<pair<K, V>> pairs = keyValuePairs();
        primeIdx++;
        buckets.assign(PRIMES[primeIdx], {}); // Resize empty out the buckets
        count = 0;
        for (auto& p : pairs) {
            set(p.first, p.second);
        }
    }

public:
    AssociativeArray() : buckets(PRIMES[0]) {}

    // insert k -> v, overwrite if k already there
    void set(const K& k, const V& v) {
        bool exist = false;
        if (buckets[indexOf(k)].empty()) {
            buckets[indexOf(k)].push_back({k, v});
            count++;
        } else {
            for (auto& p : buckets[indexOf(k)]) {
                if (p.first == k) {
                    p.second = v;
                    exist = true;
                    break;
                }
            }
            if (!exist) {
                buckets[indexOf(k)].push_back({k, v});
                count++;
            }
        }

        if (!exist && count > MAX_LOAD * PRIMES[primeIdx]) 
            rehash();
    }

    bool contains(const K& k) const {
        for (auto& p : buckets[indexOf(k)]) {
            if (p.first == k) {
                return true;
            }
        }
        return false;
    }

    // value for k, or nullopt if missing
    optional<V> get(const K& k) const {
        for (auto& p : buckets[indexOf(k)]) {
            if (p.first == k) {
                return p.second;
            }
        }
        // doesn't exist
        return nullopt;
    }

    // true if k was found and removed
    bool remove(const K& k) {
        auto& bucket = buckets[indexOf(k)];
        for (auto it = bucket.begin(); it != bucket.end(); it++) {
            if (it->first == k) {
                bucket.erase(it);
                count--;
                return true;
            }
        }

        // doesn't exist
        return false;
    }

    size_t size() const { return count; }

    vector<pair<K, V>> keyValuePairs() const {
        vector<pair<K, V>> pairs;
        for (size_t i=0; i<buckets.size(); i++) {
            for (auto& p : buckets[i]) {
                pairs.push_back(p);
            }
        }
        return pairs;
    }
};
