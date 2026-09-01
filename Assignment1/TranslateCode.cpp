#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <assert.h>
using namespace std;

/* Old Python code for reference:
def most_frequent_word(words):
    counts = {}

    for word in words:
        word = word.lower()
        counts[word] = counts.get(word, 0) + 1

    best_word = ""
    best_count = 0

    for word, count in counts.items():
        if count > best_count or (count == best_count and word < best_word):
            best_word = word
            best_count = count

    return best_word, best_count


words = ["Apple", "banana", "apple", "pear", "Banana", "apple"]
word, count = most_frequent_word(words)
print(word, count)
*/

/*
    I think translating python into C++ is a slightly harder than the other way round,
    maybe because C++ is statically typed.
*/

/* This function converts all characters in a string to lower case iteratively */
string to_lower(string str){
    for (char &c : str) {
        c = tolower(static_cast<unsigned char>(c));
    }
    return str;
}

/* This funcion finds and returns the more frequent word occured in a given array*/
string most_frequent_word(vector<string> words){
    unordered_map<string, int> counts;
    for (int i=0; i<words.size(); i++){
        counts[to_lower(words[i])]++;
    } 

    string best_word = "";
    int best_count = 0;

    for (auto &count : counts){
        if ((count.second > best_count) || (count.second == best_count && count.first < best_word)){
            best_word = count.first;
            best_count = count.second;
        }
    }

    return best_word;
}

int main() {
    // Testing my function
    assert(to_lower("Apple") == "apple");
    vector<string> words = {"Apple", "banana", "apple", "pear", "Banana", "apple"};
    string ans = most_frequent_word(words);
    assert(ans == "apple");
    return 0;
}




