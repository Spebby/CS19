/**
 * @file cs19_compact_string_set_autocomplete_test.cpp
 *
 * An interactive test of our specialized string set.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <set>
#include "cs19_compact_string_set.h"

int main(int argc, char **argv) {
  // Populate a set with all word-like tokens in a file (e.g. /srv/datasets/joyce-ulysses.txt)
  cs19::CompactStringSet dictionary;
  std::set<std::string> control_set;
  std::ifstream input_file(argv[1]);
  for (std::string word; input_file >> word;) {
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    word.erase(word.begin(), std::find_if(word.begin(), word.end(), ::isalpha));
    word.erase(std::find_if(word.rbegin(), word.rend(), ::isalpha).base(), word.end());
    dictionary.insert(word);
    control_set.insert(word);
  }
  assert(dictionary.size() == control_set.size());
  std::set<std::string> from_iterators(dictionary.begin(), dictionary.end());
  assert(from_iterators == control_set);
  std::cerr << "Set loaded with " << dictionary.size() << " strings.\n\n";
  // Query it! (e.g. under 50, rose 15, ab 100, n 500)
  std::string query;
  int num;
  for (std::cout << "> "; std::cin >> query >> num; std::cout << "> ") {
    auto suggestions = dictionary.autocomplete(query, num);
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);
    std::copy(suggestions.begin(), suggestions.end(),
              std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << '\n';
  }
}