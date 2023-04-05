/**
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */

#include <cs19_hsv_color.h>
#include <string>
#include <sstream>

namespace cs19 {
    class HsvColor {
        public:


        HsvColor(float hue, float saturation, float value) {
            if (hue < 0 || hue > 360)
                throw std::domain_error("Hue is not in domain [0, 360]");
            if (saturation < 0 || saturation > 1)
                throw std::domain_error("Saturation is not in domain [0, 1]");
            if (value < 0 || value > 1)
                throw std::domain_error("Value is not in domain [0, 1]");
            
            _hue = hue;
            _saturation = saturation;
            _value = value;
        }

        HsvColor operator~() const {
            return HsvColor(_hue + 180, _saturation, _value);
        }

        HsvColor operator|(const HsvColor &that) const {
            float hue = (_hue + that._hue) / 2;
            float saturation = (_saturation + that._saturation) / 2;
            float value = (_value + that._value) / 2;
            return HsvColor(hue, saturation, value);
        }

        HsvColor grayscale() const {
            return HsvColor(_hue, 0, _value);
        }

        std::string to_hex_string() const {
            // convert RGB to hex
            char rHex[3], gHex[3], bHex[3];
            sprintf(rHex, "%X", _red); //convert number to hex
            sprintf(gHex, "%X", _green);
            sprintf(bHex, "%X", _blue);
            std::string hexString = "#" + std::string(rHex)
                + std::string(gHex) + std::string(bHex);
            return hexString;
        }

        std::string to_rgb_string() const {
            return "rgb(" + std::to_string(_red) + ", " + std::to_string(_green) +
                    ", " + std::to_string(_blue) + ")";
        }

        // i miss '=>' (expression-bodied members)
        float hue() const { return _hue; }
        float saturation() const { return _saturation; }
        float value() const { return _value; }
        
        int red() const { return _red; }
        int green() const { return _green; }
        int blue() const { return _blue; }

        private:
        float _hue;  // [0, 360]
        float _saturation;  // [0, 1]
        float _value;  // [0, 1]
        float _red;  // [0, 255]
        float _green;  // [0, 255]
        float _blue;  // [0, 255]
    };
}  // namespace CS19