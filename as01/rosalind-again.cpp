#include <iostream>
#include <string>

int main() {
    float _density = 0;
    int _length = 0;
    while(!std::cin.eof()) {
        std::string input;
        std::cin >> input;

        for (int i = 0; (unsigned)i < input.length(); i++) {
            if (input[i] == 'G' || input[i] == 'C') {
                _density++;
            } else if (input[i] != 'A' && input[i] != 'T') {
                input.erase(i, 1);
                i--;
            }
        }
        _length += input.length();
    }

    std::cout << _density / _length * 100 << std::endl;
    return 0;
}