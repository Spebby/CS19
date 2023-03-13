#include <iostream>

namespace testing {
    int main() {
        // c out, flush the buffer. endl is optional.
        // importing all of std is bad practice, we only need two functions
        std::cout << "Hello World!" << std::endl;
    }
}  // namespace testing