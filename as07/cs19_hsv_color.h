/**
 * @author Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 */


#ifndef CS19_HSV_COLOR_H_
#define CS19_HSV_COLOR_H_

#include <string>

namespace cs19 {
    class HsvColor {
        public:
        /**
         * Constructs a new HsvColor with the given HSV components
         * @param hue the hue component of the color
         * @param saturation the saturation component of the color
         * @param value the value component of the color
         * @throw std::domain_error if any component is out of range.
         */
        HsvColor(float hue, float saturation, float value);

        /**
         * @return the complementary color, with the hue shifted 180 degrees.
         */
        HsvColor operator~() const;
        /**
         * @param that the color to the right of the operator; the comparison.
         * @return a color that is linerly interpolated between this color and another.
         */
        HsvColor operator|(const HsvColor &that) const;

        /**
         * @return the greyscale (desaturated) version of this color.
         */
        HsvColor grayscale() const;

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

        // may or may not actually exist?
        float hue() const;
        float saturation() const;
        float value() const;
        int red() const;
        int green() const;
        int blue() const;
    };
}  // namespace cs19

#endif  // CS19_HSV_COLOR_H_
