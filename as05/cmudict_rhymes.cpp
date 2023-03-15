/**
 * @file cmudict_rhymes.cpp
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
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

namespace cs19 {

    void read_dictionary(std::istream& in, std::unordered_map<std::string, std::string>& dict) {
        std::ifstream dataset("/srv/datasets/cmudict/cmudict.dict");
        std::string phoneme;
        std::string word;
        // file line contents: Word\ARPAPronunciation
        while (dataset >> word && dataset.seekg(1, std::ios_base::cur) &&
            std::getline(dataset, phoneme)) {
            dict[phoneme] = word;
        }
    }

    void print_dictionary(const std::unordered_map<std::string, std::string>& dict) {
        for (auto& entry : dict)
            std::cout << entry.first << " " << entry.second << std::endl;
    }

    void print_rhymes(const std::string& word) {
        std::cout << "hi" << std::endl;
    }

    int main(int argc, char **argv) {
        // read in the dictionary
        std::unordered_map<std::string, std::string> CMUdict;
        cs19::read_dictionary(std::cin, CMUdict);
        // DEBUG: print the dictionary
        cs19::print_dictionary(CMUdict);
        cs19::print_rhymes(argv[1]);

        return 0;
    }
    // wow apparently main doesn't exist!!!
}  // namespace cs19