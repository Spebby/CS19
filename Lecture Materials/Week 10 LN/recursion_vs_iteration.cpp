/**
 * @file week10.cpp
 * @brief CS 19: Week 10 Lecture
 * @details This file contains the code for the lecture on week 10
 * @author Jeffrey Bergamini for CS 19
*/

#include <iostream>
#include <chrono>
#include <unordered_map>
#include <cstdint>

namespace cs19 {
    /**
     * @brief Computes the factorial of a number using basic recursion.
     * @param n The number to compute the factorial of
    */
    uint64_t factorial_recursive(uint64_t n) {
        if (n == 0)
            return 1;
        else
            return n * factorial_recursive(n - 1);
    }
    /**
     * @brief Computes the factorial of a number using basic recursion.
     * @param n The number to compute the factorial of
    */
    int factorial_recursive(int n) {
        if (n == 0)
            return 1;
        else
            return n * factorial_recursive(n - 1);
    }

    /**
     * @brief Computes the factorial of a number using basic recursion.
     * @param n The number to compute the factorial of
    */
   uint64_t factorial_iterative(uint64_t n) {
        uint64_t result = 1;
        while (n > 1) {
            result *= n--;
        }
        return result;
    }

    /**
     * @brief Computes the factorial of a number using iteration.
     * @param n The number to compute the factorial of
    */
    int factorial_iterative(int n) {
        int result = 1;
        while (n > 1) {
            result *= n--;
        }
        return result;
    }

    /**
     * @brief Computes the nth Fibonacci number using iteration.
     * @param n The index of the Fibonacci number to compute
     * @param call_count A pointer to a counter that will be incremented each time this function is called.
     * @return The nth Fibonacci number
     * @note This function is not recursive.
    */
    uint64_t fibonacci_iterative(__uint64_t n, uint64_t *call_count) {
        ++*call_count;
        if (n < 2)
            return n;
        uint64_t fib[] = {0, 1, 1};  // fib[n-2], fib[n-1], fib[n]

        while (n-- > 2) {
            fib[0] = fib[1];
            fib[1] = fib[2];
            fib[2] = fib[0] + fib[1];
        }

        return fib[2];  // fib[n]
    }

    /**
     * @brief Computes the nth Fibonacci number using iteration.
     * @param n The index of the Fibonacci number to compute
     * @return The nth Fibonacci number
     * @note This function is not recursive.
    */
    uint64_t fibonacci_iterative(__uint64_t n) {
        if (n < 2)
            return n;
        uint64_t fib[] = {0, 1, 1};  // fib[n-2], fib[n-1], fib[n]

        while (n-- > 2) {
            fib[0] = fib[1];
            fib[1] = fib[2];
            fib[2] = fib[0] + fib[1];
        }

        return fib[2];  // fib[n]
    }

    /**
     * @brief Computes the nth Fibonacci number using basic recursion.
     * @param n The index of the Fibonacci number to compute
     * @param call_count A pointer to a counter that will be incremented each time this function is called.
     * @return The nth Fibonacci number
     * @note This function is tail recursive.
     * @note This slows down as n gets larger. The call counts get into hundreds of millions of calls.
    */
    uint64_t fibonacci_recursive(__uint64_t n, uint64_t *call_count) {
        ++*call_count;
        if (n < 2)
            return n;
        return fibonacci_recursive(n - 1, call_count) + fibonacci_recursive(n - 2, call_count);
    }

    /**
     * @brief Computes the nth Fibonacci number using basic recursion.
     * @param n The index of the Fibonacci number to compute
     * @return The nth Fibonacci number
     * @note This function is tail recursive.
     * @note This slows down as n gets larger. The call counts get into hundreds of millions of calls.
    */
    uint64_t fibonacci_recursive(__uint64_t n) {
        if (n < 2)
            return n;
        return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
    }

    /**
     * @brief A helper function for computing memoized Fibonacci numbers.
     * @param n The index of the Fibonacci number to compute
     * @param call_count A pointer to a counter that will be incremented each time this function is called.
     * @param memos A pointer to a map that will store previously computed Fibonacci numbers.
     * @return The nth Fibonacci number
    */
    uint64_t fibonacci_memoized(uint64_t n, uint64_t *call_count,
                                std::unordered_map<uint64_t, uint64_t> *memos) {
        ++*call_count;
        if (n < 2)
            return n;
        // Memoization:
        // Have we already calculated the nth Fibonacci number?
        auto entry = memos->find(n);
        if (entry == memos->end()) {
            // no: we have not calculated the nth Fib yet
            auto result =
                fibonacci_memoized(n - 1, call_count, memos) + fibonacci_memoized(n - 2, call_count, memos);
            (*memos)[n] = result;
            return result;
        }
        return entry->second;  // second will be value associated with key n
    }
    
    /**
     * @brief Computes the nth Fibonacci number.
     * @param n The index of the Fibonacci number to compute
     * @param call_count A pointer to a counter that will be incremented each time this function is called.
     * @return The nth Fibonacci number
     * @note This is fast, but slows down as n gets larger. The call counts get into hundreds of millions of calls.
    */
    uint64_t fibonacci_memoized(uint64_t n, uint64_t *call_count) {
        std::unordered_map<uint64_t, uint64_t> memos;  // key: n, value: Fib number
        ++*call_count;
        return fibonacci_memoized(n, call_count, &memos);
    }

    /**
     * @brief A helper function for computing memoized Fibonacci numbers. This is not intended to be called directly.
     * @param n The index of the Fibonacci number to compute.
     * @param memos A pointer to a map that will store previously computed Fibonacci numbers.
     * @return The nth Fibonacci number
     * @note This is fast, but slows slightly down as n gets larger. The call counts grows linearly by 2.
    */
    uint64_t fibonacci_memoized(uint64_t n, std::unordered_map<uint64_t, uint64_t> *memos) {
        if (n < 2)
            return n;
        // Memoization:
        // Have we already calculated the nth Fibonacci number?
        auto entry = memos->find(n);
        if (entry == memos->end()) {
            // no: we have not calculated the nth Fib yet
            auto result =
                fibonacci_memoized(n - 1, memos) + fibonacci_memoized(n - 2, memos);
            (*memos)[n] = result;
            return result;
        }
        return entry->second;  // second will be value associated with key n
    }
    
    /**
     * @brief Computes the nth Fibonacci number.
     * @param n The index of the Fibonacci number to compute
     * @return The nth Fibonacci number
     * @note This is fast, but slows slightly down as n gets larger. The call counts grows linearly by 2.
    */
    uint64_t fibonacci_memoized(uint64_t n) {
        uint64_t call_count = 0;
        return fibonacci_memoized(n, &call_count);
    }
}

/**
 * For now:
 *   - With one command-line argument, runs the iterative Fibonacci calculation
 *   - With two command-line arguments, runs the recursive Fibonacci calculation
 *   - With three command-line arguments, runs the memoized recursion Fibonacci calculation
 *
 * ./a.out 6
 * ./a.out 6 x
 * ./a.out 6 x x
 *
 * @param argc expected to be at least 2
 * @param argv expects at least argv[0] contains a nonnegative integer (Fibonacci index)
 */
int main(int argc, char **argv) {
    uint64_t n = std::stoi(argv[1]);
    uint64_t result;
    uint64_t call_count = 0;
    auto before = std::chrono::high_resolution_clock::now();
    std::string description;
    if (argc > 3) {
        result = cs19::fibonacci_memoized(n, &call_count);
        description = "Memoized";
    } else if (argc > 2) {
        result = cs19::fibonacci_recursive(n, &call_count);
        description = "Recursive";
    } else {
        result = cs19::fibonacci_iterative(n, &call_count);
        description = "Iterative";
    }

    auto after = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(after - before).count();
    // old c way of printing
    std::printf("%s fib %2ld = %15ld  call count: %12ld  time: %ld ns\n", description.data(), n,
                result, call_count, duration);
}