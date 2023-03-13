/**
 * @file stl_vector.cpp
 *
 * Simple illustration of STL vector.
 * Try: cut -f 1 /srv/datasets/turnins_per_student_per_assignment | ./a.out
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */
 
#include <algorithm>  // std::sort()
#include <iostream>   // std::cin
#include <numeric>    // std::accumulate()
#include <string>
#include <vector>

namespace testing {
    int main() {
    // Fill a vector with ints from stdin
        std::vector<int> data;
        std::cerr << "sizeof(int) on this system is " << sizeof(int) << " bytes.\n";
        auto capacity = data.capacity();
        std::cerr << "data.size() == " << data.size() << "\tdata.capacity() == " << capacity << " ("
                    << sizeof(int) * data.capacity() << " bytes)\tdata.data() == " << data.data() << '\n';
        for (int val; std::cin >> val;) {
            data.push_back(val);
            if (data.capacity() != capacity) {
            capacity = data.capacity();
            std::cerr << "data.size() == " << data.size() << "\tdata.capacity() == " << capacity << " ("
                        << sizeof(int) * data.capacity() << " bytes)\tdata.data() == " << data.data()
                        << '\n';
            }
        }
        // Notice that many of the handy STL functions require iterators!
        std::sort(data.begin(), data.end());  // std::sort is pretty quick with vectors
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
        double median = data[data.size() / 2];
        if (data.size() % 2 == 0)
            median = (median + data[data.size() / 2 - 1]) / 2;
        std::cout << "Total values: " << data.size() << '\n'
                    << "Mean: " << mean << '\n'
                    << "Median: " << median << '\n';
    }
}  // namespace testing