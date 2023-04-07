#include <iostream>
#include "cs19_hsv_color.h"

int main() {
  constexpr int DIMENSION = 32;
  std::cout << "<html lang=en>"
               "<head>"
               "  <meta charset=utf-8>"
               "  <title>CS 19 HSV Color Demo</title>"
               "  <style>"
               "    .colorbox { display: inline-block; width: 25px; height: 25px; padding: 0px; }"
               "  </style>"
               "</head>"
               "<body>"
               "<section>"
               "<header>"
               "<h1>"
            << DIMENSION
            << "-hue horizontal gradient, full saturation, descending value vertical gradient</h1>"
               "<h3>Hovering over a color shows its complementary color.</h3>"
               "</header>";
  for (int row = 0; row < DIMENSION; ++row) {
    for (int col = 0; col < DIMENSION; ++col) {
      float hue = 360.0f * col / DIMENSION;
      float saturation = 1;
      float value = 1.0f - static_cast<float>(row) / DIMENSION;
      cs19::HsvColor color(hue, saturation, value);
      std::cout << "<div class='colorbox' style='background-color: " << color.to_hex_string()
                << ";' onmouseover='this.style.backgroundColor = \"" << (~color).to_hex_string()
                << "\";' onmouseout='this.style.backgroundColor = \"" << color.to_hex_string()
                << "\";'></div>";
    }
    std::cout << "<br>";
  }
  std::cout << "</section>"
               "<section>"
               "<header>"
               "<h1>"
            << DIMENSION
            << "-hue horizontal gradient, descending saturation vertical gradient, full value</h1>"
               "<h3>Hovering over a color shows its complementary color.</h3>"
               "</header>";
  for (int row = 0; row < DIMENSION; ++row) {
    for (int col = 0; col < DIMENSION; ++col) {
      float hue = 360.0f * col / DIMENSION;
      float saturation = 1.0f - static_cast<float>(row) / DIMENSION;
      float value = 1;
      cs19::HsvColor color(hue, saturation, value);
      std::cout << "<div class='colorbox' style='background-color: " << color.to_hex_string()
                << ";' onmouseover='this.style.backgroundColor = \"" << (~color).to_hex_string()
                << "\";' onmouseout='this.style.backgroundColor = \"" << color.to_hex_string()
                << "\";'></div>";
    }
    std::cout << "<br>";
  }
  std::cout << "</section>"
               "<section>"
               "<header>"
               "<h1>"
            << DIMENSION
            << "-hue horizontal gradient, full saturation, descending value vertical gradient, "
               "displayed in grayscale</h1>"
               "<h3>Hovering over a color shows the original (non-grayscale) color.</h3>"
               "</header>";
  for (int row = 0; row < DIMENSION; ++row) {
    for (int col = 0; col < DIMENSION; ++col) {
      float hue = 360.0f * col / DIMENSION;
      float saturation = 1;
      float value = 1.0f - static_cast<float>(row) / DIMENSION;
      cs19::HsvColor color(hue, saturation, value);
      std::cout << "<div class='colorbox' style='background-color: "
                << color.grayscale().to_hex_string()
                << ";' onmouseover='this.style.backgroundColor = \"" << color.to_hex_string()
                << "\";' onmouseout='this.style.backgroundColor = \""
                << color.grayscale().to_hex_string() << "\";'></div>";
    }
    std::cout << "<br>";
  }
  std::cout << "</section>"
               "</body>"
               "</html>";
}