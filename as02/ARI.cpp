#include <iostream>  // std::c(in|out)
#include <sstream>   // std::istringstream
#include <string>    // std::getline

/*
ARI Definition:
4.71(characters/words) + 0.5(words/sentences) − 21.43

Characters is the total number of English-letter characters A–Z, case-insensitive.
Words are all any word containing at least one letter, separated by whitespace.
Sentences are indicated by any word containing at least one letter prior to a '.', '?', '!'.
*/
 
int main() {
    int _characters = 0, _words = 0, _sentences = 0;
    constexpr unsigned BUFFERSIZE = 8192;
    char buffer[BUFFERSIZE];


    for (std::cin.read(buffer, BUFFERSIZE); std::cin.gcount() > 0;
    std::cin.read(buffer, BUFFERSIZE)) {
        // tokenise dis bitch
        
        switch (buffer[0]) {
            case '.':
            case '?':
            case '!':
                _sentences++;
                break;
            default:
                isalpha(buffer[0]) ? _characters++ : _words++;
                isspace(buffer[0]) ? _words++ : _characters++;
                break;
        }   
    }
    // currently doesn't work as intended. Investigate!
    printf("%.3f", (4.71 * (_characters / _words) + 0.5 * (_words / _sentences) - 21.43));
}

int count_words(const std::string &line) {
    // const: this function is not allowed to change the state of object "line"
    // &line: string object will be passed "by reference", i.e. the original object instead of a copy
    int word_count = 0;
    std::istringstream line_stream(line);  // Lets us treat a string like an input/output stream
    // Extraction operator evaluates to true if input stream not in a fail/EOF state
    for (std::string token; line_stream >> token;)
        ++word_count;
        return word_count;
}