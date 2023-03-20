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

bool all = false;
int syllables = 0;
std::string query;

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
std::unordered_set<std::string>>& dict) {
    std::ofstream outfile("outputTest.txt");
    for (auto& entry : dict) {
        std::string entries;
        for (auto& word : entry.second)
            entries += word + " ";
        // remove the last space
        entries = entries.substr(0, entries.length() - 1);
        outfile << entry.first << " " << entries << std::endl;
    }

    std::cout << "Size: " << dict.size() << std::endl;
}

void print_rhymes(const std::set<std::string>& NUCI, std::unordered_map<std::string,
    std::unordered_set<std::string>>& DICT) {
    // search the dict for words that end with the same phoneme
    std::set<std::string> rhymes;
    for (std::pair<const std::string,
    std::unordered_set<std::string>>& entry : DICT) {
        for (auto& nunc : NUCI) {
            const std::string& phoneme = entry.first;
            if (!all) {
                int temp_syll = 0;
                for (auto& c : phoneme)
                    if (c == '0' || c == '1' || c == '2')
                        temp_syll++;
                if (temp_syll != syllables)
                    continue;
            }
            if (phoneme.length() >= nunc.length() &&
                phoneme.substr(phoneme.length() - nunc.length()) == nunc) {
                    rhymes.insert(entry.second.begin(), entry.second.end());
            }
        }
    }

    rhymes.erase(query);
    for (auto& word : rhymes)
        std::cout << word << std::endl;
}

int main(int argc, char **argv) {
    // check that we recieved a string from the command line
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <word> <arg>" << std::endl;
        return 1;
    }

    if (argc == 3 && std::string(argv[2]) == "-a")
        all = true;

    std::unordered_map<std::string,
    std::unordered_set<std::string>> CMUdict;
    read_dictionary(std::cin, CMUdict);
    // print_dictionary(CMUdict);  // DEBUG: print the dictionary

    query = (std::string)argv[1];
    for (char &c : query)
        c = tolower(c);

    // std::cout << "Query: " << query << std::endl;
    std::set<std::string> nunciations;
    for (std::pair<const std::string,
    std::unordered_set<std::string>>& entry : CMUdict) {
        for (auto& word : entry.second) {
            if (word == query) {  // word is found: find the last stressed phoneme
                auto pho = entry.first;
                // find out the number of syllables
                // integer suffixed phonemes designate end of a syllable.
                if (!all) {
                    syllables = 0;
                    for (char& c : pho)
                        if (c == '0' || c == '1' || c == '2')
                            syllables++;
                            // std::cout << "Syllables: " << syllables << std::endl;
                }

                for (std::size_t i = pho.length() - 1; i >= 0; i--) {
                    if (pho[i] == '1' || pho[i] == '2') {
                        nunciations.insert(pho.substr(i - 2));
                        // std::cout << "Phoneme: " << pho.substr(i - 2) << std::endl;
                        break;
                    }
                }
            }
        }
    }
    if (nunciations.empty()) {
        // std::cerr << "Word not found in dictionary." << std::endl;
        return 1;
    }
    print_rhymes(nunciations, CMUdict);

    return 0;
}