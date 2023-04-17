#ifndef CS19_SEARCH_SORT_H_
#define CS19_SEARCH_SORT_H_

/**
 * @file cs19_search_sort.h
 * @brief Header file for CS 19's search and sort functions
 * @author  Thom Mott for CS 19, tomott@jeff.cis.cabrillo.edu
 * This assignment has the limitation of not allowing any #include directives.
 */
namespace cs19 {

    /**
     * Swaps the values of two variables.
     *
     * @tparam T a type that supports `operator=`
     *
     * @param a a variable
     * @param b a variable
     */
    template<typename T >
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    /**
     * Returns an iterator to the first element in the range `[first,last)` that compares equal to
     * `val`. If no such element is found, the function returns `last`.
     *
     * @tparam Iterator a position iterator that supports the [standard input iterator
     * operations](http://www.cplusplus.com/reference/iterator/InputIterator/)
     * @tparam Value a value type that supports `operator==`
     *
     * @param first the initial position in the sequence to be sorted
     * @param last one element past the final position in the sequence to be sorted
     * @param val the value for which to search
     * @return an iterator to the first element in the range that compares equal to `val`. If no
     * elements match, the function returns `last`.
     */
    template <typename Iterator, typename Value>
    Iterator linear_search(Iterator first, Iterator last, const Value &val) {
        if (first == last)  // empty range
            return last;

        while (first != last) {
            if (*first == val)
                return first;

            ++first;
        }
        return last;
    }

    /**
     * Performs an index-based linear search on an index-able object for a given value.
     *
     * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
     * elements must be of template type `Value`.
     * @tparam Value a value type that supports `operator==`
     *
     * @param haystack the object to search
     * @param needle the value for which to search
     * @return the first index found via linear search at which `haystack` contains `needle`, or `-1` if
     * `haystack` does not contain `needle`
     */
    template <typename IndexedContainer, typename Value>
    int linear_search(const IndexedContainer &haystack, const Value &needle) {
        auto size = static_cast<int>(haystack.size());
        for (auto i = 0; i < size; ++i)
            if (haystack[i] == needle)
                return i;
        // returns last
        return -1;
    }

    /**
     * Performs an index-based binary search on an index-able object for a given value.
     * @note Expects data to be pre-sorted.
     * 
     * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
     * elements must be of template type `Value`.
     * @tparam Value a value type that supports `operator==` and `operator<`
     *
     * @param haystack the object to search
     * @param needle the value for which to search
     * @return the first index found via binary search at which `haystack` contains `needle`, or `-1` if
     * `haystack` does not contain `needle`
     */
    template <typename IndexedContainer, typename Value>
    int binary_search(const IndexedContainer &haystack, const Value &needle) {
        int low = 0;
        int high = static_cast<int>(haystack.size()) - 1;
        while (low <= high) {
            int mid = (low + high)/2;
            if (haystack[mid] == needle)
                return mid;
            else if (haystack[mid] < needle)
                low = mid + 1;
            else
                high = mid - 1;
        }
        // if nothing is found
        return -1;
    }

    /**
     * Performs an index-based bubble sort on any index able container object.
     * @note Worst Case: O(n^2)
     * @note Best Case: O(n)
     *
     * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
     * elements must support `operator<` and `operator=`.
     *
     * @param values the object to sort
     */
    template <typename IndexedContainer>
    void bubble_sort(IndexedContainer &values) {
        auto max = static_cast<int>(values.size());
        for (auto step = 0; step < max; ++step)
            // compare elements
            for (auto i = 0; i < (max - 1); ++i)
                // compare adjacent
                if (values[i] > values[i + 1])
                    swap(values[i], values[i + 1]);
    }

    /**
     * Sorts the elements in the range `[first,last)` into ascending order, using the bubble-sort
     * algorithm. The elements are compared using `operator<`.
     * @note Worst Case: O(n^2)
     * @note Best Case: O(n)
     *
     * @tparam Iterator a position iterator that supports the [standard bidirectional iterator
     * operations](http://www.cplusplus.com/reference/iterator/BidirectionalIterator/)
     *
     * @param first the initial position in the sequence to be sorted
     * @param last one element past the final position in the sequence to be sorted
     */
    template <typename Iterator>
    void bubble_sort(Iterator first, Iterator last) {
        if (first == last)  // empty range
            return;

        bool swapped;
        do {
            swapped = true;
            auto current = first, next = first; ++next;
            while (next != last) {
                if (*current > *next) {
                    cs19::swap(*current, *next);
                    swapped = false;
                }
                current = next;
                ++next;
            }
        } while (!swapped);
    }

    /**
     * Performs an index-based selection sort on an index-able object.
     * @note Worst Case: O(n^2)
     * @note Best Case: O(n^2)
     *
     * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
     * elements must support `operator<` and `operator=`.
     *
     * @param values the object to sort
     */
    template <typename IndexedContainer>
    void selection_sort(IndexedContainer &values) {
        auto length = static_cast<int>(values.size());
        for (auto step = 0; step < length - 1; ++step) {
            int min = step;
            // find min
            for (auto check = step + 1; check < length; ++check)
                if (values[check] < values[min])
                    min = check;

            cs19::swap(values[step], values[min]);
        }
    }

    /**
     * Sorts the elements in the range `[first,last)` into ascending order, using the selection-sort
     * algorithm.
     * @note Worst Case: O(n^2)
     * @note Best Case: O(n^2)
     *
     * @tparam Iterator a position iterator that supports the [standard input iterator
     * operations](http://www.cplusplus.com/reference/iterator/InputIterator/)
     *
     * @param first the initial position in the sequence to be sorted
     * @param last one element past the final position in the sequence to be sorted
     */
    template <typename Iterator>
    void selection_sort(Iterator first, Iterator last) {
        for (Iterator step = first; step != last; ++step) {
            Iterator min = step;
            // find min
            auto next = step;
            ++next;
            for (Iterator i = next; i != last; ++i)
                if (*i < *min)
                    min = i;

            cs19::swap(*step, *min);
        }
    }

}  // namespace cs19
#endif  // CS19_SEARCH_SORT_H_