/**
 * @file countdown.cpp
 * @brief This program decrements the input to 1.
 * 
 * This is an example of a program that takes a command line argument.
 * 
 * @author Jeffery Bergamini for CS 19, jeffery.bergamini@cabrillo.edu
*/

#include <iostream>
#include <string>

int main(int argc, char **argv) {
    // argc: number of arguments passed to the program
    // argv: array of arguments passed to the program
    // argv[0] is the name of the program
    // argv[1...n] is the nth argument passed to the program

    int x = std::stoi(argv[1]);
    while (x >= 0) {
        std::cout << x << '\n';
        --x;
    }
}