/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    std::string curLine;
    std::ifstream file(word_list_fname);
    if (file.is_open()) {
        while (getline(file, curLine)) {
            if (curLine.size() == 5) {
                std::string w1 = curLine.substr(1, curLine.size() - 1);
                std::string w2 = curLine[0] + curLine.substr(2, curLine.size() - 1);
                if (d.homophones(curLine, w1) && d.homophones(curLine, w2)) {
                    ret.push_back(std::tuple<std::string, std::string, std::string>(curLine, w1, w2));
                }
            }
        }
    }
    return ret;
}
