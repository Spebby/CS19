/**
 * @file hi_again.cpp
 *
 * Let's talk about why and how this program dies.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */
#include <cstdint>
#include <iostream>
 
/** This function calls itself, which will cause it to call itself again, and then again, and... */
void say_hi() {
    static uint64_t count = 0;  // static local variable: persists for duration of program
    std::cerr << "Hi " << count++ << '\n';
    say_hi();  // recursion involves repetition, but not with a loop!
}

/**
 * This function calls itself, which will cause it to call itself again, and then again, and...
 * @note This version doesn't use a static variable, as a result it will fill up the stack much quicker.
*/
void say_hi(uint64_t count) {
    std::cerr << "Hi " << count << '\n';
    say_hi(count + 1);  // recursion involves repetition, but not with a loop!
}

/** This will not end well... */
int main() {
  say_hi();
}