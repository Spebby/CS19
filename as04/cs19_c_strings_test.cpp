// Double quotes after #include implies a file path relative to this file.
// The following will if work cs19_c_strings.h is in the same directory as this file.
#include "cs19_c_strings.h"
#include "cs19_c_strings.cpp"
#include <cassert>
#include <iostream>
 
int main() {
    char msg[] = "12345";
    assert(cs19::atoi(msg) == 12345);
    assert(cs19::strlen(msg) == 5);
    assert(cs19::strpbrk(msg, "abc543") == msg + 2);
  
    char s1[] = "hello";
    char s2[] = "123";
    char s3[100];
    cs19::strzip(s1, s2, s3);
    assert(!cs19::strcmp(s3, "h1e2l3lo"));

    // write some tests for strstr
    assert(cs19::strstr(s1, "llo") == s1 + 2);
    std::cout << "All tests passed!" << std::endl;
}