/**
 * @file set_spell_checker.cpp
 *
 * Quick and dirty spell checker, printing misspelled words one per line to stdout.
 * std::set.contains() uses a binary search
 * std::unordered_set.contains() uses a hash table-based search
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_set>
 
int main(int argc, char** argv) {
  // std::set<std::string> dictionary;  // choose this data structure...
  std::unordered_set<std::string> dictionary;  // or this one
 
    {
        std::string dict_file_path(argc > 1 ? argv[1] : "/usr/share/dict/words");
        // file for spell-checking dictionary
        std::ifstream dict_file(dict_file_path);
        for (std::string word; std::getline(dict_file, word);) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            dictionary.insert(word);
        }
        std::cerr << "(Dictionary from file " << dict_file_path << " has " << dictionary.size()
                << " words.)\n";
    }
 
  // Copy "words" (whitespace-delimited tokens, trimmed of non-English letters) to stdout, one word
  // per line, if not found in the dictionary (case-insensitive).
    for (std::string word; std::cin >> word;) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(word.begin(), std::find_if(word.begin(), word.end(), ::isalpha));
        word.erase(std::find_if(word.rbegin(), word.rend(), ::isalpha).base(), word.end());
        
        // the below code fails if before C++20
        if (!word.empty() && !dictionary.contains(word))
            std::cout << word << '\n';
    }
}