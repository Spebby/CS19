#include <iostream>

int main()
{
    std::string input;
    std::cin >> input;
    float _density;
    // get the percentage of C and G's in input
    for (int i = 0; i < input.length(); i++)
        if (input[i] == 'C' || input[i] == 'G')
            _density++;
    std::cout << (_density / input.length() * 100) << std::endl;
    return 0;
}