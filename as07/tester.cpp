#include "cs19_hsv_color.cpp"
#include <cassert>
#include <iostream>
#include <vector>

int main() {
    // create a HSV colour with hue 0, saturation 1, value 1
    /*cs19::HsvColor red(0, 1, 1);
    cs19::HsvColor green(120, 1, 1);
    cs19::HsvColor blue(240, 1, 1);
    cs19::HsvColor yellow(60, 1, 1);
    cs19::HsvColor cyan(180, 1, 1);
    cs19::HsvColor magenta(300, 1, 1);
    cs19::HsvColor white(0, 0, 1);
    cs19::HsvColor test(0, 0.99, 1);*/
    cs19::HsvColor cornflower(219, 0.58, 0.93);
    cs19::HsvColor dumb(360, 1, 1);
    std::vector<cs19::HsvColor> colours;
    colours.push_back(cornflower);
    colours.push_back(dumb);

    for (auto colour : colours) {
        // print the name of the colour
        
        std::cout << "HSV: " << colour.to_string() << ", " << colour.to_rgb_string()
        << ", HEX: " << colour.to_hex_string() << std::endl;
        auto comp = ~colour;
        std::cout << "Complementry: " << comp.to_string() << ", "
        << comp.to_rgb_string() << ", HEX: " << comp.to_hex_string() << std::endl;
    }
}