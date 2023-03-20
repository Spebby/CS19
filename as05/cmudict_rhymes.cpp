/**
 * @file cmudict_rhymes.cpp
 * @brief Reads a CMU Pronouncing Dictionary file and fills a set with the words.
 * 
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <iterator>

void read_dictionary(std::istream& in,
std::unordered_map<std::string, std::unordered_set<std::string>>& dict) {
    std::ifstream dataset("/srv/datasets/cmudict/cmudict.dict");
    std::string phoneme, word;
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

void print_rhymes(const std::set<std::string>& NUCI, const std::unordered_map<std::string,
    std::unordered_set<std::string>>& DICT, const std::string& query,
    const short syllables, const bool all) {
    // search the dict for words that end with the same phoneme
    std::set<std::string> rhymes;
    for (const auto& entry : DICT) {
        for (const auto& nunc : NUCI) {
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
    for (const auto& word : rhymes)
        std::cout << word << "\n";
}

int main(int argc, char **argv) {
    if (argc < 2)  // check that we recieved a string from the command line
        return 1;

    bool all = false;
    if (argc == 3 && std::string(argv[2]) == "-a")
        all = true;

    std::unordered_map<std::string,
    std::unordered_set<std::string>> CMUdict;
    read_dictionary(std::cin, CMUdict);
    // print_dictionary(CMUdict);  // DEBUG: print the dictionary

    
    short syllables = 0;
    std::string query(argv[1]);
    std::transform(query.begin(), query.end(), query.begin(), [](unsigned char c) 
    { return std::tolower(c); });
    query.erase(std::remove_if(query.begin(), query.end(), [](unsigned char c) {
        return !std::isalpha(c) && c != '\'' && c != '-';
    }), query.end());

    // std::cout << "Query: " << query << std::endl;
    std::set<std::string> nunciations;
    for (const auto& entry : CMUdict) {
        for (const auto& word : entry.second) {
            if (word == query) {  // word is found
                auto pho = entry.first;
                // integer suffixed phonemes designate end of a syllable.
                if (!all) {
                    syllables = 0;
                    for (char& c : pho)
                        if (c == '0' || c == '1' || c == '2')
                            syllables++;
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
    print_rhymes(nunciations, CMUdict, query, syllables, all);
}