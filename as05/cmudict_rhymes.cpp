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
 * If query word has two possible pronunciations, use both (do seperate analysis on both)
 * and then combine results.
 * USE A SET AT THE END. Automatically removes double words and is alphabetical.
 * Saves time + faster to read.
 * 
 * @param dict The set to fill with words.
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

void read_dictionary(std::istream& in, std::unordered_map<std::string, std::string>& dict) {
    std::ifstream dataset("/srv/datasets/cmudict/cmudict.dict");
    std::string phoneme;
    std::string word;
    // file line contents: Word\ARPAPronunciation
    while (dataset >> word && dataset.seekg(1, std::ios_base::cur) &&
        std::getline(dataset, phoneme)) {
        // if the the 3rd to last character of a word is a (, remove the end of the string
        if (word[word.length() - 3] == '(')
            word = word.substr(0, word.length() - 3); 

        dict[phoneme] = word;
    }
}

void print_dictionary(const std::unordered_map<std::string, std::string>& dict) {
    for (auto& entry : dict)
        std::cout << entry.first << " " << entry.second << std::endl;
    
    std::cout << "Size: " << dict.size() << std::endl;
    std::cout << "Done" << std::endl;
}

void print_rhymes(const std::string& word) {
    std::cout << "Rhymes for " << word << std::endl;
    std::set<std::string> rhymes;
}

int main(int argc, char **argv) {
    // read in the dictionary
    // check that we recieved a string from the command line
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <word>" << std::endl;
        return 1;
    }

    std::unordered_map<std::string, std::string> CMUdict;
    read_dictionary(std::cin, CMUdict);
    // DEBUG: print the dictionary
    print_dictionary(CMUdict);
    std::string query = argv[1];
    std::cout << "Query: " << query << std::endl;
    print_rhymes(query);

    return 0;
}