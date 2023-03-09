/**
 * @file cmudict_rhymes.cpp
 *
 * @brief A program that reads a CMU Pronouncing Dictionary file and prints all words that rhyme
 *       with a given word.
 *
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */

#include <iostream>

// 


int main() {
    
}

/*
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
 
int main() {
  std::unordered_map<int, std::string> zip_codes;
  int zip;
  {
    std::ifstream zipcities("/srv/datasets/zipcities");
    int zip_code;
    std::string city_state;
    // file line contents: ZIP\tCity, State
    while (zipcities >> zip_code && zipcities.seekg(1, std::ios_base::cur) &&
           std::getline(zipcities, city_state)) {
      zip_codes[zip_code] = city_state;
    }
  }
  while (std::cin >> zip)
    std::cout << zip_codes[zip] << '\n';
}
*/