/**
 * @file cmudict_rhymes.cpp
 *
 * @brief A program that reads a CMU Pronouncing Dictionary file and prints all words that rhyme
 *       with a given word.
 *
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

// 
namespace cs19 {

    int main() {
        // read in the dictionary
        std::set<std::string> CMUdict;
        cs19::read_dictionary(std::cin, CMUdict);

        
    }

    // take in data and fill a set
    void read_dictionary(std::istream& in, std::set<std::string>& dict) {
        int entry;
        {
            std::ifstream dataset("/srv/datasets/cmudict/cmudict.dict");
            int index;
            std::string ARPA;
            while (dataset >> index && dataset.seekg(1, std::ios_base::cur) &&
            std::getline(dataset, ARPA)) {
                dict[index] = ARPA;
            }
        }
        while (std::cin >> entry)
            std::cout << dict[entry] << '\n';
    }

    void print_rhymes(const std::string& word) {
        
    }
}  // namespace cs19 