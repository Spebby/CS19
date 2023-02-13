#include <iostream>
#include <string>

/*
ARI Definition:
4.71(characters/words) + 0.5(words/sentences) − 21.43

Characters are all non whitespace characters, A-Z case insensitive.
Words are all sequences of characters separated by whitespace.
Sentences are all sequences of words separated by . ! or ?.
*/
 
int main() {
    int _characters = 0, _words = 0, _sentences = 0;
    constexpr unsigned BUFFERSIZE = 8192;
    char buffer[BUFFERSIZE];
    for (std::cin.read(buffer, BUFFERSIZE); std::cin.gcount() > 0;
    std::cin.read(buffer, BUFFERSIZE)) {
        for (unsigned i = 0; i < std::cin.gcount(); i++) {
            switch (buffer[i]) {
                case ' ':
                    _words++;
                    break;
                case '.':
                case '!':
                case '?':
                    _sentences++;
                    break;
                default:
                    _characters++;
            }
        }
    }
    printf("%.3f", 4.71 * (_characters / _words) + 0.5 * (_words / _sentences) - 21.43);
}