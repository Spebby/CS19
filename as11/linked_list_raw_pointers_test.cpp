2/**
 * @file linked_list_raw_pointers_test.cpp
 *
 * Exercising our proto-linked-list demo.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */
#include "linked_list_raw_pointers.h"
#include <iostream>
#include <string>

int main() {
  cs19::LinkedList<char> test_list{'H', 'e', 'l', 'l', 'o'};  // heap allocation
  std::cout << test_list << '\n';
  test_list.push_back('!');  // heap allocation
  std::cout << test_list << '\n';
  test_list.push_front('>');  // heap allocation
  std::cout << test_list << '\n';
  cs19::LinkedList<double> test_list2{1.111, 2.222, 3.333};  // heap allocation
  std::cout << test_list2 << '\n';
  cs19::LinkedList<std::string> test_list3{"BE", "HERE", "NOW"};  // heap allocation
  std::cout << test_list3 << '\n';
  // test_list3 destroyed
  // test_list2 destroyed
  // test_list destroyed
}