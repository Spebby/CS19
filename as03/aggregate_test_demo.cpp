/**
 * @file aggregate_test_demo.cpp
 *
 * Assertion-based tests for functions in cs19_aggregate.h.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */
 
#include <cassert>
#include <string>
#include <vector>
 
#include "cs19_aggregate.h"
 
int main() {
  assert(cs19::all(std::string("CS 19!")));
  assert(!cs19::all(std::vector<int>{2, 4, 6, 0, 1}));
  assert(!cs19::all(std::vector<bool>{true, true, false, true}));
  assert(cs19::any(std::string("CS 19!")));
  assert(cs19::any(std::vector<int>{2, 4, 6, 0, 1}));
  assert(!cs19::any(std::vector<bool>{false, false, false, false}));
  assert(cs19::max(std::vector<int>{2, 4, 6, 0, 1}) == 6);
  assert(cs19::min(std::vector<int>{2, 4, 6, 0, 1}) == 0);
  assert(cs19::sum(std::string("CS 19!"), 0) == 321);
  assert(cs19::sum(std::vector<int>{2, 4, 6, 0, 1}, 0.0) == 13.0);
}