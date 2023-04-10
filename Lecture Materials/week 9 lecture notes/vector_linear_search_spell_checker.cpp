/**
 * @file vector_linear_search_spell_checker.cpp
 *
 * Quick and dirty spell checker, printing misspelled words one per line to stdout.
 * std::find() uses a linear search.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
 
int main(int argc, char** argv) {
  std::vector<std::string> dictionary;  // choose this data structure...
  {
    std::string dict_file_path(argc > 1 ? argv[1] : "/usr/share/dict/words");
    // file for spell-checking dictionary
    std::ifstream dict_file(dict_file_path);
    for (std::string word; std::getline(dict_file, word);) {
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
      dictionary.push_back(word);
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
    if (!word.empty() && std::find(dictionary.begin(), dictionary.end(), word) == dictionary.end())
      std::cout << word << '\n';
  }
}