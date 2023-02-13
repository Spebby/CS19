#include <iostream>
#include <string>

int main() {
    float _gcDensity = 0, _atDensity = 0;
    constexpr unsigned BUFFERSIZE = 8192;
    // no need to check eof, if gcount is less then buffer length, we're at the end.
    char buffer[BUFFERSIZE];
    for (std::cin.read(buffer, BUFFERSIZE); std::cin.gcount() > 0;
    std::cin.read(buffer, BUFFERSIZE)) {
        for (unsigned i = 0; i < std::cin.gcount(); i++) {
            switch (buffer[i]) {
                case 'G':
                case 'C':
                    _gcDensity++;
                    break;
                case 'A':
                case 'T':
                    _atDensity++;
                    break;
            }
        }
    }

    printf("%f\n", (_gcDensity / (_gcDensity + _atDensity + .000000001) * 100));
    return 0;
}