#include <iostream>

int main() {
    std::string input;
    std::cin >> input;
    float _density = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == 'G' || input[i] == 'C') {
            _density++;
        } else if (input[i] != 'A' && input[i] != 'T') {
            input.erase(i, 1);
            i--;
        }
    }
    std::cout << _density / input.length() * 100 << std::endl;
    return 0;
}