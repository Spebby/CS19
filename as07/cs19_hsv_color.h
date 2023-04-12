/**
 * @file cs19_hsv_color.h
 * @brief Header file for CS 19's HsvColor class
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */


#ifndef CS19_HSV_COLOR_H_
#define CS19_HSV_COLOR_H_

#include <string>

namespace cs19 {
    class HsvColor {
        public:
        /** Constructs a new HsvColor with all components set to 0. */
        HsvColor();
        
        /**
         * Constructs a new HsvColor with the given HSV components
         * @param hue the hue component of the color
         * @param saturation the saturation component of the color
         * @param value the value component of the color
         * @throw std::domain_error if any component is out of range.
         */
        HsvColor(float hue, float saturation, float value);

        /** @return the complementary color, with the hue shifted 180 degrees. */
        HsvColor operator~() const;
        /**
         * @param that the color to the right of the operator; the comparison.
         * @return a color that is linerly interpolated between this color and another.
         */
        HsvColor operator|(const HsvColor &that) const;

        /** @return the greyscale (desaturated) version of this color. */
        HsvColor grayscale() const;

        /**
         * @return Returns string representation of the color in the format
         * "hsv(60, 1, 1)"
         * @see https://www.w3schools.com/cssref/css_colors_legal.php
         */
        std::string to_string() const;

        /**
         * @return Returns a CSS-compatible color string in 24-bit RGB hexadecimal format, e.g.
         * "#000000" for black and "#6495ed" for cornflower blue.
         *
         * @see https://www.w3schools.com/cssref/css_colors_legal.php
         */
        std::string to_hex_string() const;

        /**
         * @return Returns a CSS-compatible color string in 24-bit RGB decimal format, e.g.
         * "rgb(0,0,0)" for black and "rgb(100, 149, 237)" for cornflower blue.
         *
         * @see https://www.w3schools.com/cssref/css_colors_legal.php
         */
        std::string to_rgb_string() const;

        /** @return The hue component of the color */
        float hue() const;
        /** @return The saturation component of the color */
        float saturation() const;
        /** @return The value component of the color */
        float value() const;
        /** @return The red component of the color */
        int red() const;
        /** @return The green component of the color */
        int green() const;
        /** @return The blue component of the color */
        int blue() const;

        private:
        float _hue;  // [0, 360]
        float _saturation;  // [0, 1]
        float _value;  // [0, 1]
        unsigned int _red;  // [0, 255]
        unsigned int _green;  // [0, 255]
        unsigned int _blue;  // [0, 255]
    };
}  // namespace cs19
#endif  // CS19_HSV_COLOR_H_
