/**
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */

#include "cs19_hsv_color.h"
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

namespace cs19 {
    HsvColor::HsvColor() {
        _hue = _saturation = _value = _red = _green = _blue = 0;
        // cpp style, according to jeff.
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

        float chroma = saturation * value;
        float huePrime = hue / 60;
        float X = chroma * (1 - abs(fmod(huePrime, 2) - 1));
        std::vector<float> RGB;

        if (huePrime >= 5) {
            RGB = {chroma, 0, X};
        } else if (huePrime >= 4) {
            RGB = {X, 0, chroma};
        } else if (huePrime >= 3) {
            RGB = {0, X, chroma};
        } else if (huePrime >= 2) {
            RGB = {0, chroma, X};
        } else if (huePrime >= 1) {
            RGB = {X, chroma, 0};
        } else {
            RGB = {chroma, X, 0};
        }

        float diff = value - chroma;
        _red = std::round((RGB[0] + diff) * 255);
        _green = std::round((RGB[1] + diff) * 255);
        _blue = std::round((RGB[2] + diff) * 255);
    }

    HsvColor HsvColor::operator~() const {
        // to future me: this is fmod because % sucks; mainly due to C backwards compatability.
        float newHue = fmod((_hue + 180), 360);
        return HsvColor(newHue, _saturation, _value);
    }
    HsvColor HsvColor::operator|(const HsvColor &that) const {
        float hue = (_hue + that.hue()) / 2;
        float saturation = (_saturation + that.saturation()) / 2;
        float value = (_value + that.value()) / 2;
        return HsvColor(hue, saturation, value);
    }

    HsvColor HsvColor::grayscale() const { return HsvColor(_hue, 0, _value); }

    std::string HsvColor::to_string() const {
        int hue = static_cast<int>(_hue);
        int saturation = static_cast<int>(_saturation * 100);
        int value = static_cast<int>(_value * 100);
        return "hsv(" + std::to_string(hue) + ", " + std::to_string(saturation) +
                "%, " + std::to_string(value) + "%)";
    }

    std::string HsvColor::to_hex_string() const {
        // can't just do "std::blah hex << stuff" because the object
        // has to be created first, thus the need for a new line.

        std::stringstream hex;
        hex << std::hex << std::setfill('0') << std::setw(2) << _red
        << std::setw(2) << _green << std::setw(2) << _blue;
        // can be uppercase to be retro; old hexcodes were uppercase.
        // the setfill and setw are to make sure that the hexcode is 6 digits long.
        //     previously, if val = 0, it would be 0, not 00.
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