/** @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu */

#include <cassert>
#include <list>
#include <string>
#include <iostream>
#include <vector>
#include "cs19_search_sort.h"
 
int main() {
    std::string data = "a1b2c3";
    cs19::bubble_sort(data);
    assert(data == "123abc");
    data = "Santa Cruz";
    cs19::selection_sort(data);
    assert(data == " CSaanrtuz");
    // more selection sort tests
    std::vector<int> v = {5, 4, 3, 2, 1};
    cs19::selection_sort(v);
    assert(v == std::vector<int>({1, 2, 3, 4, 5}));
    assert(cs19::linear_search(data, 'a') == 3);
    assert(cs19::binary_search(data, 'S') == 2);
    assert(cs19::binary_search(data, '!') == -1);

    // test the cs19::swap function
    int a = 1;
    int b = 2;
    cs19::swap(a, b);
    assert(a == 2);
    std::vector test = {1, 2, 3};
    // swap the first and second element
    cs19::swap(test[0], test[1]);
    assert(test[0] == 2);

    std::list<int> more_data = {5, 4, 3, 2, 1};
    cs19::bubble_sort(more_data.begin(), more_data.end());
    assert(more_data == std::list<int>({1, 2, 3, 4, 5}));
    assert(cs19::linear_search(more_data.begin(), more_data.end(), 1) == more_data.begin());
    assert(cs19::linear_search(more_data.begin(), more_data.end(), 0) == more_data.end());
	std::cout << "All tests passed!" << std::endl;
	return 0;
}