/**
 * @file cmudict_rhymes.cpp
 * @brief Reads a CMU Pronouncing Dictionary file and fills a set with the words.
 * 
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <iterator>

/*void print_dictionary(const std::unordered_map<std::string,
std::set<std::pair<std::string, int16_t>>>& dict) {
    std::ofstream outfile("outputTest.txt");
    for (const auto& entry : dict) {
        outfile << entry.first << " ";
        for (const auto& word : entry.second)
            outfile << word.first << ", " << word.second << " ";
        outfile << std::endl;
    }
    std::cout << "Size: " << dict.size() << std::endl;
}*/

void print_rhymes(const std::set<std::pair<std::string, int16_t>>& NUCI, const
    std::unordered_map<std::string, std::set<std::pair<std::string,
    int16_t>>>& DICT, const bool& all) {
    // search the dict for words that end with the same phoneme
    std::set<std::string> rhymes;
    // since the dict should now have the same phoneme for each word, we can just
    // search for the phoneme in the query word.
    for (const auto& entry: NUCI) {
        auto it = DICT.find(entry.first)->second;
        // insert some code here to get the set from the dict
        if (!all) {
            std::set<std::string> tempRhymes;
            for (const auto& word : it) {
                if (word.second == entry.second)
                    tempRhymes.insert(word.first);
            }
            rhymes.insert(tempRhymes.begin(), tempRhymes.end());
        } else {
            for (const auto& word : it)
                rhymes.insert(word.first);
        }
        // then check each pair in the set to see if the syll count isn't too long if not all
        // then insert the word into the rhymes set
    }

    for (const auto& word : rhymes)
        std::cout << word << "\n";
}

int main(int argc, char **argv) {
    if (argc < 2)  // check that we recieved a string from the command line
        return 1;

    bool all = false;
    if (argc == 3 && std::string(argv[2]) == "-a")
        all = true;

    // FUN FACT: YOU CAN MAKE SETS OF PAIRS!!!!
    std::unordered_map<std::string, std::set<std::pair<std::string, int16_t>>> CMUdict;
    std::string query(argv[1]);
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);
    // don't need anything to remove "illegal characters" since command line args removes "'s
    std::set<std::pair<std::string, int16_t>> nunciations;
    // micro optimisation would be to make this a vector and reserve.
    std::ifstream dataset("/srv/datasets/cmudict/cmudict.dict");
    std::string fingerprint, word;
    // file line contents: Word\ARPAPronunciation

    // instead of full phonemes, you could instead only care about the "rhyme pattern"
    while (dataset >> word && dataset.seekg(1, std::ios_base::cur) &&
        std::getline(dataset, fingerprint)) {
        if (word.back() == ')')
            word = word.substr(0, word.length() - 3);

        // integer suffixed phonemes designate end of a syllable.
        int16_t temptSyll = 0;
        if (!all) {
                for (char& c : fingerprint)
                    if (c == '0' || c == '1' || c == '2')
                        temptSyll++;
        }
        std::string tempPhoneme;
        // if the fingerprint has a 1 or 2 in it, then use find the substring
        // from the last 1 or 2 to the end of the string
        if (fingerprint.find('1') != std::string::npos 
        || fingerprint.find('2') != std::string::npos) {
            tempPhoneme = fingerprint.substr(fingerprint.find_last_of("12") - 2);
        } else
            tempPhoneme = fingerprint;

        if (word == query) {
            nunciations.insert(std::make_pair(tempPhoneme, temptSyll));
            continue;
        }
        
        CMUdict[tempPhoneme].insert(std::make_pair(word, temptSyll));
    }
    // print_dictionary(CMUdict);  // DEBUG: print the dictionary
    if (nunciations.empty())
        return 1;

    print_rhymes(nunciations, CMUdict, all);
}