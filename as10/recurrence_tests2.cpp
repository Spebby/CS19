/**
 * @author Thom Mott for CS 19
*/

#include <gmpxx.h>
#include <cmath>
#include <cstdint>
#include <iostream>
#include "cs19_recurrence.h"

int main() {
    std::cout << "What function should be used?\n" 
            << "1. phi\n" 
            << "2. rho\n" 
            << "3. fibonacci\n" 
            << "4. padovan\n" 
            << "5. perrin\n" 
            << "6. most_precise" << std::endl;
    
    int choice;
    std::cin >> choice;
    if (std::cin.fail() || choice < 1 && choice > 6) {
        std::cout << "Invalid choice" << std::endl;
        return 0;
    }
    std::cout << "What number should be tested? Enter any non-number value to quit." << std::endl;
    bool keepTesting = true;
    
    // while loop to keep testing, user can type 'q' to quit. test is done by calling the function
    // with the number the user entered and printing the result
    while (keepTesting) {
        int number;
        std::cin >> number;
        if (std::cin.fail()) {
            keepTesting = false;
            break;
        }
        auto result = 0;
        std::cout << "Result: ";
        switch (choice) {
            case 1:
                std::cout << cs19::phi(number) << std::endl;
                break;
            case 2:
                std::cout << cs19::rho(number) << std::endl;
                break;
            case 3:
                std::cout << cs19::fibonacci(number) << std::endl;
                break;
            case 4:
                std::cout << cs19::padovan(number) << std::endl;
                break;
            case 5:
                std::cout << cs19::perrin(number) << std::endl;
                break;
            case 6:
                std::cout << cs19::most_precise(cs19::phi) << std::endl;
                break;
        }
    }
}