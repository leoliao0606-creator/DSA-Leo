#pragma once
#include <string>
#include <bitset>
#include <vector>
#include "AssociativeArray.hpp"
using namespace std;

// text -> '0'/'1' string, 8 bits per char
string textToBits(const string& text) {
    string result;
    for (char c : text) {
        result += bitset<8>(c).to_string();
    }
    return result;
}

// '0'/'1' string -> text, 8 bits per char
string bitsToText(const string& bits) {
    string result;
    for (size_t i=0; i<bits.size(); i+=8) {
        result += static_cast<char>(bitset<8>(bits.substr(i, 8)).to_ulong());
    }
    return result;
}

// how many bits to write any index in [0, j)
size_t bitsFor(size_t j) {
    size_t n = 0;
    while ((size_t(1) << n) < j) n++;
    return n;
}

// x -> n-bit '0'/'1' string
string toBinary(size_t x, size_t n) {
    string s;
    for (size_t i = n; i > 0; i--) s += ((x >> (i - 1)) & 1) ? '1' : '0';
    return s;
}

// '0'/'1' string -> number
size_t fromBinary(const string& s) {
    size_t x = 0;
    for (char c : s) x = x * 2 + (c - '0');
    return x;
}

// LZ78 encode: bits in, compressed bits out.
// each new phrase = (index of longest known prefix) + 1 new bit
string lzEncode(const string& bits) {
    AssociativeArray<string, int> book;  // phrase -> index
    book.set("", 0);
    string out, cur;
    size_t j = 1;  // index of the next new phrase
    for (char b : bits) {
        if (book.contains(cur + b)) {
            cur += b;
            continue;
        }
        out += toBinary(*book.get(cur), bitsFor(j)) + b;
        book.set(cur + b, j++);
        cur = "";
    }
    // leftover phrase is already in the book, so just write its index
    if (!cur.empty()) out += toBinary(*book.get(cur), bitsFor(j));
    return out;
}

// undo lzEncode
string lzDecode(const string& code) {
    vector<string> book = {""};  // index -> phrase
    string out;
    size_t i = 0;
    while (i < code.size()) {
        size_t n = bitsFor(book.size());
        string prefix = book[fromBinary(code.substr(i, n))];
        i += n;
        // no bit left after the index -> it was the leftover phrase
        if (i == code.size()) {
            out += prefix;
            break;
        }
        book.push_back(prefix + code[i++]);
        out += book.back();
    }
    return out;
}
