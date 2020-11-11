/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    string curLine;
    std::ifstream file(filename);
    if (file.is_open()) {
        while (getline(file, curLine)) {
            string curWord = curLine;
            std::sort(curWord.begin(), curWord.end());
            dict[curWord].push_back(curLine);
        }
    }
    file.close();
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (auto curWord : words) {
        string sortedWord = curWord;
        std::sort(sortedWord.begin(), sortedWord.end());
        dict[sortedWord].push_back(curWord);
    }

}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string sortedWord = word;
    std::sort(sortedWord.begin(), sortedWord.end());
    //not contained or no anagrams found
    if (dict.find(sortedWord) == dict.end() || dict.at(sortedWord).size() == 1) return vector<string>();
    return dict.at(sortedWord);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    std::vector<std::vector<std::string>> res;
    for (auto ana : dict) {
        if (ana.second.size() > 1) res.push_back(ana.second);
    }
    return res;
}
