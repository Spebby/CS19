/**
 * @file cmudict_rhymes.cpp
 * @brief Reads a CMU Pronouncing Dictionary file and fills a set with the words.
 * 
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <iterator>

void read_dictionary(std::istream& in,
std::unordered_map<std::string, std::unordered_set<std::string>>& dict) {
    std::ifstream dataset("/srv/datasets/cmudict/cmudict.dict");
    std::istream_iterator<std::string> word_it(dataset), eof;
    while (word_it != eof) {
        std::string word = *word_it++;
        if (word.back() == ')')
            word.resize(word.length() - 3);
        std::string phoneme = *word_it++;
        dict.emplace(std::move(phoneme), std::unordered_set<std::string>{std::move(word)});
    }
}

int main(int argc, char **argv) {
    std::unordered_map<std::string,
    std::unordered_set<std::string>> CMUdict;
    read_dictionary(std::cin, CMUdict);
}