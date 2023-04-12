/**
 * @file stack_heap_raii.cpp
 *
 * Local variables are allocated on the stack.
 * "new" reserves memory on the heap. "delete" marks it as no longer in use.
 * Heap-allocated memory stays allocated until deleted.
 * RAII: "Resource Acquisition is Initialization"
 *   (Objects are destroyed when they pass out of scope.)
 *
 * Try:
 * # openat/close --> open/close file, mmap/munmap --> allocate/deallocate heap space
 * strace --trace=openat,close,mmap,munmap ./a.out
 * valgrind ./a.out
 * valgrind --leak-check=full --show-leak-kinds=all ./a.out
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// appends the contents of an array of ints to a file, as decimal integer text values, one per line
void append_to_file(int *array, std::size_t array_len, const std::string &file_path) {
  // all of the following are local (stack-allocated) variables:
  //   parameters array, array_len, file_path
  //   locals out_file, i
  std::ofstream out_file(file_path, std::ofstream::app);
  for (std::size_t i = 0; i < array_len; ++i) {
    out_file << array[i] << '\n';
  }  // i passes out of scope. It is a fundamental type (unsigned integer), so no destructor.
  // out_file passes out of scope: Destructor (std::ofstream::~ofstream) will be called.
  //   std::ofstream::~ofstream estructor will "close" the file, release resources back to OS, etc.
  //   (You don't need to (and shouldn't) manually call out_file.close().)
  // file_path, array_len, array pass out of scope.
  //   file_path is a compound type, but since it is a reference, the object's lifetime doesn't end.
  //   array_len and array are fundamental types, so no destructor is called.
}

int main(int argc, char **argv) {
    std::cerr << "main() has been called.\n";
    std::srand(std::time(0));  // seed the old C-library random number generator with the current time
    std::size_t total_memory_allocated = 0;

    for (std::size_t array_len; std::cin >> array_len;) {
        int *array = new int[array_len];  // dynamic memory allocation: reserves space on the heap
        std::cerr << "Allocated " << array_len * sizeof(int) << " bytes @" << array
                  << " for an array of " << array_len << " int values\n";
        for (std::size_t i = 0; i < array_len; ++i)
            array[i] = std::rand();  // fill array with pseudorandom integers
        append_to_file(array, array_len, "random_numbers.txt");
        total_memory_allocated += array_len * sizeof(int);
        delete[] array;  // deallocates memory
        // "array" passes out of scope. If we don't deallocate the memory, we create a memory leak.
    }  // "array_len" passes out of scope. It is just an integer; no destructor is called.

    std::cerr << "Manually allocated " << total_memory_allocated << " bytes total for int arrays.\n";
    {  // anonymous block for scoping purposes
        std::vector<int> data;
        std::size_t num_values = std::rand() % 1000000 + 1000000;  // choose a random number in [1M,2M)
        std::cerr << "About to push " << num_values << " ints into a vector...("
                  << num_values * sizeof(int) << " bytes required)\n";
        while (num_values--)
            data.push_back(std::rand());  // vector will need to do several new/delete for its array
            // num_values passes out of scope. It is a fundamental type; no destructor.
            // data passes out of scope. std::vector::~vector will deallocate the internal array.
        std::cerr << "vector will now be destroyed!\n";
    }
    // total_memory_allocated passes out of scope. It is a fundamental type; no destructor.
    // argv passes out of scope. It is a fundamental type; no destructor.
    // argc passes out of scope. It is a fundamental type; no destructor.
    std::cerr << "main() is returning.\n";
}