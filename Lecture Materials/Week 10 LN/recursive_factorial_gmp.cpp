/**
 * @file recursive_factorial_gmp.cpp
 *
 * The classic recursive n!, now using GMP for arbitrary-precision integers.
 * Must tell GCC to include the GMP libraries:
 *   g++ recursive_factorial_gmp.cpp -lgmp -lgmpxx
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */
#include <gmpxx.h>
#include <cstdint>
#include <iostream>
#include <vector>

mpz_class factorial(const mpz_class &n) {
  if (n < 2)  // Base cases: We know by definition that 0! = 1 and 1! = 1
    return 1;
  return n * factorial(n - 1);  // Recursive step: Otherwise, n! = n * (n - 1)!
}

int main(int argc, char **argv) {
  auto value = mpz_class(argv[1]);
  std::cout << value << "! = " << factorial(value) << '\n';
}