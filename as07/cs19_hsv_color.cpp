/**
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */

#include <string>
#include <sstream>
#include <iostream>
#include "cs19_hsv_color.h"

namespace cs19 {
    HsvColor::HsvColor() {
        _hue, _saturation, _value, _red, _green, _blue = 0;
    }

    HsvColor::HsvColor(float hue, float saturation, float value) {
        if (hue < 0 || hue > 360)
            throw std::domain_error("Hue is not in domain [0, 360]");
        if (saturation < 0 || saturation > 1)
            throw std::domain_error("Saturation is not in domain [0, 1]");
        if (value < 0 || value > 1)
            throw std::domain_error("Value is not in domain [0, 1]");

        _hue = hue;
        _saturation = saturation;
        _value = value;

        // convert from HSV to RGB
        auto max = value;
        auto chroma = saturation * max;
        auto min = max - chroma;
        auto huePrime = hue / 60;
        float rgb[3] = {0, 0, 0};  // this may FUCK everything up. check
        if (-1 <= huePrime < 1) {
            if (huePrime - 0 < 0)
                float rgb[3] = {max, min, min - (huePrime * chroma)};
            else if (huePrime - 0 >= 0)
                float rgb[3] = {max, min + (huePrime * chroma), min};
        } else if (1 <= huePrime < 3) {
            if (huePrime - 2 < 0)
                float rgb[3] = {min + (huePrime - 2) * chroma, max, min};
            else if (huePrime - 2 >= 0)
                float rgb[3] = {min, max, min - (huePrime - 2) * chroma};
        } else if (3 <= huePrime < 5) {
            if (huePrime - 4 < 0)
                float rgb[3] = {min, min + (huePrime - 4) * chroma, max};
            else if (huePrime - 4 >= 0)
                float rgb[3] = {min - (huePrime - 4) * chroma, min, max};
        }
        
        _red = rgb[0] * 255;
        _green = rgb[1] * 255;
        _blue = rgb[2] * 255;
    }

    HsvColor HsvColor::operator~() const {
        return HsvColor(static_cast<int>(_hue + 180) % 360, _saturation, _value);
    }
    HsvColor HsvColor::operator|(const HsvColor &that) const {
        float hue = (_hue + that.hue()) / 2;
        float saturation = (_saturation + that.saturation()) / 2;
        float value = (_value + that.value()) / 2;
        return HsvColor(hue, saturation, value);
    }

    HsvColor HsvColor::grayscale() const { return HsvColor(_hue, 0, _value); }

    std::string HsvColor::to_hex_string() const {
        // can't just do "std::blah hex << stuff" because the object
        // has to be created first, thus the need for a new line.
        std::stringstream hex;
        hex << std::hex << _red;
        hex << std::hex << _green;
        hex << std::hex << _blue;
        // because stringstream is a stream like cout, I can just insert more into it.
        return "#" + hex.str();
    }

    std::string HsvColor::to_rgb_string() const {
        return "rgb(" + std::to_string(_red) + ", " + std::to_string(_green) +
                ", " + std::to_string(_blue) + ")";
    }

    // i miss '=>' (expression-bodied members)
    float HsvColor::hue() const { return _hue; }
    float HsvColor::saturation() const { return _saturation; }
    float HsvColor::value() const { return _value; }
    int HsvColor::red() const { return _red; }
    int HsvColor::green() const { return _green; }
    int HsvColor::blue() const { return _blue; }
}  // namespace cs19