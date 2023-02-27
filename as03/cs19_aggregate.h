/**
 * @file cs19_aggregate.h
 *
 * Template functions offering some convenient aggregations.
 *
 * @author Someone in CS 19, someone@jeff.cis.cabrillo.edu
 */

// Header guard: ensures that the contents of this file will only be added once to an executable
#ifndef CS19_AGGREGATE_H_
#define CS19_AGGREGATE_H_

namespace cs19
{
    /**
     * Returns `true` if any element of an iterable object is `true`.
     *
     * @tparam Iterable an iterable type that supports iteration with a range-based loop, and
     *         contains values convertible to `bool`.
     *
     * @param data an iterable collection of values convertible to `bool`
     * @return `true` if any element of `data` is `true`
     */
    template <typename Iterable>
    bool any(const Iterable &data)
    {
        for (const auto &element : data)
            if (element)
                return true;

        return false;
    }

    /**
     * Returns `true` if all elements of an iterable object are `true` (or if the iterable is empty).
     *
     * @tparam Iterable an iterable type that supports iteration with a range-based loop, and
     *         contains values convertible to `bool`.
     *
     * @param data an iterable collection of values convertible to `bool`
     * @return `true` if all elements of `data` are `true` (or if the iterable is empty)
     */
    template <typename Iterable>
    bool all(const Iterable &data)
    {
        auto length = 0;
        for (const auto &element : data)
            ++length;
        if(length == 0)
            return true;

        for (const auto &element : data)
            if (!element)
                return false;
        
        return true;
    }

    /**
     * Returns the largest element of an iterable object.
     *
     * @tparam Iterable an iterable type that supports iteration with a range-based loop, and
     *         contains values of type `Element`
     * @tparam Element a type that can be value-initialized and of which instances are mutually
     *         comparable using the < operator
     * @see https://en.cppreference.com/w/cpp/language/value_initialization
     *
     * @param data an iterable collection of `Element` values, assumed to be non-empty
     * @return the largest element of `data`
     */
    template <template <typename> typename Iterable, typename Element>
    Element max(const Iterable<Element> &data)
    {
        auto bookkeep = Element();
        for (const auto &element : data)
            if (element > bookkeep)
                bookkeep = element;
        
        return bookkeep;
    }

    /**
     * Returns the smallest element of an iterable object.
     *
     * @tparam Iterable an iterable type that supports iteration with a range-based loop, and
     *         contains values of type `Element`
     * @tparam Element a type that can be value-initialized and of which instances are mutually
     *         comparable using the < operator
     * @see https://en.cppreference.com/w/cpp/language/value_initialization
     *
     * @param data an iterable collection of `Element` values, assumed to be non-empty
     * @return the smallest element of `data`
     */
    template <template <typename> typename Iterable, typename Element>
    Element min(const Iterable<Element> &data)
    {
        auto bookkeep = Element();
        for (const auto &element : data)
            if (element < bookkeep)
                bookkeep = element;

        return bookkeep;
    }

    /**
     * Returns the sum of all elements in an iterable object.
     *
     * @tparam Iterable an iterable type that supports iteration with a range-based loop, and
     *         contains values valid as operands to the + operator along with a value of type `SumType`
     * @tparam SumType a type that can is copy-constructible, copy-assignable, and of which instances
     *         are valid as operands to the + operator along with an element from an `Iterable` instance
     * @see https://en.cppreference.com/w/cpp/named_req/CopyConstructible
     * @see https://en.cppreference.com/w/cpp/named_req/CopyAssignable
     *
     * @param data an iterable collection
     * @param start the initial value for the sum
     * @return the sum of all elements in `data`
     */
    template <typename Iterable, typename SumType>
    SumType sum(const Iterable &data, SumType start)
    {
        for (const auto &element : data)
            start += element;

        return start;
    }

} // namespace cs19

#endif // CS19_AGGREGATE_H_