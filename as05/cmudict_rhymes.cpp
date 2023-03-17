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
#include <unordered_set>

// currently does not read in properly!
// When a word with the same pronunciation is found, it is not added to the map. 
// ex. Rhyme and Rime.
void read_dictionary(std::istream& in,
std::unordered_map<std::string, std::unordered_set<std::string>>& dict) {
    std::ifstream dataset("/srv/datasets/cmudict/cmudict.dict");
    std::string phoneme;
    std::string word;
    // file line contents: Word\ARPAPronunciation
    while (dataset >> word && dataset.seekg(1, std::ios_base::cur) &&
        std::getline(dataset, phoneme)) {
        if (word.back() == ')')
            word = word.substr(0, word.length() - 3);
        // if the pronunciation is already in the map, add the word to the set
        dict[phoneme].insert(word);
    }
}

void print_dictionary(const std::unordered_map<std::string,
std::unordered_set<std::string>>& dict, bool fast = false) {
    std::ofstream outfile("outputTest.txt");
    if(fast) {
        for (auto& entry : dict) {
            std::string entries;
            for (auto& word : entry.second)
                entries += word + " ";
            // remove the last space
            entries = entries.substr(0, entries.length() - 1);
            outfile << entry.first << " " << entries << std::endl;
        }
    } else { 
        for (auto& entry : dict) {
            std::string entries;
            for (auto& word : entry.second)
                entries += word + " ";
            // remove the last space
            entries = entries.substr(0, entries.length() - 1);

            std::cout << entry.first << " " << entries << std::endl;
            outfile << entry.first << " " << entries << std::endl;
        }
    }

    std::cout << "Size: " << dict.size() << std::endl;
}

void print_rhymes(const std::set<std::string>& nunci, const std::unordered_map<std::string,
std::unordered_set<std::string>>& dict) {
    // find the last stressed vowel
    std::set<std::string> phonemes;
    for (auto& entry : nunci) {
        for (int i = entry.length() - 1; i >= 0; i--) {
            if (entry[i] == '1') {
                phonemes.insert(entry.substr(i - 2));
                std::cout << "Phoneme: " << entry.substr(i - 2) << std::endl;
            }
        }
    }
}

int main(int argc, char **argv) {
    // read in the dictionary
    // check that we recieved a string from the command line
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <word>" << std::endl;
        return 1;
    }

    std::unordered_map<std::string,
    std::unordered_set<std::string>> CMUdict;
    read_dictionary(std::cin, CMUdict);
    // print_dictionary(CMUdict, true);  // DEBUG: print the dictionary
    // find the rhymes, then print them.
    std::string query = (std::string)argv[1];
    // make argv lowercase
    for (int i = 0; i < query.length(); i++)
        query[i] = tolower(query[i]);
    std::cout << "Query: " << query << std::endl;
    std::set<std::string> nunciations;
    // not every word gets copied into cmudict, investigate. The below logic is sound.
    for (std::pair<const std::string,
    std::unordered_set<std::string>>& entry : CMUdict) {
        for (auto& word : entry.second)
            if (word == query) {
                nunciations.insert(entry.first);
                std::cout << "Nunciation: " << entry.first << std::endl;
        }
    }
    if (nunciations.empty()) {
        std::cerr << "Word not found in dictionary." << std::endl;
        return 1;
    }
    print_rhymes(nunciations, CMUdict);

    return 0;
}