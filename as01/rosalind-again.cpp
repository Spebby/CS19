#include <iostream>

int main() {
    std::string input;
    std::cin >> input;
    float _density;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] != 'A' && input[i] != 'T') {
            if(input[i] == 'C' || input[i] == 'G') {
                _density++;
            }
            else {
                input.erase(i, 1);
                i--;
            }
        }
    }
    std::printf("%.6f", (_density / input.length()) * 100);
    return 0;
}