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


int main() {
    // read in the dictionary
    std::unordered_map<std::string> CMUdict;
    cs19::read_dictionary(std::cin, CMUdict);

    
}

/**
 * @brief Reads a CMU Pronouncing Dictionary file and fills a set with the words.
 *
 * @param in The input stream to read from.
 * Read in the dictionary file and fill a map with ARPA as key/index and word as value.
 * ex. "AE2 B D IH0 K EY1 SH AH0 N", "Abdication"
 * When exaiming, we'd go from the last stressed (EY1) to the end. "ation"
 * For the purposes of finding the last phoneme, ignore x0's.
 * 
 * If query word has two possible pronunciations, use both (do seperate analysis on both) and then combine results. 
 * USE A SET AT THE END. Automatically removes double words and is alphabetical. Saves time + faster to read.
 * 
 * @param dict The set to fill with words.
 */

namespace cs19 {

    // take in data and fill a set
    void read_dictionary(std::istream& in, std::unordered_map<std::string>& dict) {
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
    }

    void print_rhymes(const std::string& word) {
        
    }
}  // namespace cs19 