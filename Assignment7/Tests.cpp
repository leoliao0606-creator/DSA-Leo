#include <cassert>
#include <iostream>
#include <string>
#include "AssociativeArray.hpp"
#include "LempelZiv.hpp"
using namespace std;

void testSetGet() {
    AssociativeArray<int, string> map;
    map.set(5, "Excellent");
    map.set(3, "Normal");
    map.set(1, "Bad");
    assert(map.get(3) == "Normal");
    map.set(3, "Good");
    assert(map.get(3) == "Good");
    assert(map.size() == 3);
    assert(!map.get(42));
    assert(map.contains(5) && !map.contains(42));
}

void testRemove() {
    AssociativeArray<string, int> map;
    map.set("a", 1);
    map.set("b", 2);
    assert(map.remove("a"));
    assert(!map.remove("a"));
    assert(!map.contains("a") && map.contains("b"));
    assert(map.size() == 1);
}

void testRehash() {
    AssociativeArray<string, int> map;
    for (int i = 0; i < 1000; i++) map.set(to_string(i), i);
    assert(map.size() == 1000);
    for (int i = 0; i < 1000; i++) assert(map.get(to_string(i)) == i);
}

void testKeyValuePairs() {
    AssociativeArray<string, int> map;
    map.set("a", 1);
    map.set("b", 2);
    map.set("c", 3);
    map.remove("b");
    auto pairs = map.keyValuePairs();
    assert(pairs.size() == 2);
    for (auto& p : pairs) assert(map.get(p.first) == p.second);
}

void testBits() {
    assert(textToBits("A") == "01000001");
    assert(bitsToText(textToBits("Hello")) == "Hello");
}

void testLzEncode() {
    // 1|0|11|01|010|00|10
    assert(lzEncode("1011010100010") == "100011101100001000010");
}

void testLzRoundTrip() {
    for (string bits : {"", "0", "11", "1011010100010"})  // "11" ends on a known phrase
        assert(lzDecode(lzEncode(bits)) == bits);
    for (string s : {"abababababab", "the quick brown fox"})
        assert(lzDecode(lzEncode(textToBits(s))) == textToBits(s));
}

int main() {
    testSetGet();
    testRemove();
    testRehash();
    testKeyValuePairs();
    testBits();
    testLzEncode();
    testLzRoundTrip();
    cout << "all tests passed" << endl;
}
