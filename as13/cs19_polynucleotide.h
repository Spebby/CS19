/**
 * @file cs19_polynucleotide.h
 *
 * A basic implementation of a class meant to serve as a base class for specific polynucleotides
 * such as DNA and RNA.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 * @author A Cabrillo student for CS 19, someone@jeff.cis.cabrillo.edu
 */
#ifndef _CS19_POLYNUCLEOTIDE_H
#define _CS19_POLYNUCLEOTIDE_H

#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <vector>

namespace cs19 {

/**
 * Class Polynucleotide models a class representing a mutable nucleic acid sequence, with operators
 * providing an idiomatic C++ interface, meant to serve as a base class for classes modeling
 * specific polynucleotides such as DNA and RNA.
 */
class Polynucleotide {
 public:
    // makes the function interable
    auto cbegin() const {
        return this->sequence_.cbegin();
    }
    auto cend() const {
        return this->sequence_.cend();
    }
    auto crbegin() const {
        return this->sequence_.crbegin();
    }
    auto crend() const {
        return this->sequence_.crend();
    }
    auto begin() {
        return this->sequence_.begin();
    }
    auto end() {
        return this->sequence_.end();
    }
    auto rbegin() {
        return this->sequence_.rbegin();
    }
    auto rend() {
        return this->sequence_.rend();
    }


    /**
     * Default constructor: Creates an empty sequence.
     *
     * @param complements a mapping of valid nucleotides to their complementary nucleotides
     */
    Polynucleotide(std::map<char, char> complements) {
        this->complements_ = complements;
    }

    /**
     * Copy constructor: Copies from a pre-existing Polynucleotide.
     *
     * @param extant a pre-existing Polynucleotide object
     */
    Polynucleotide(const Polynucleotide &extant) {
        this->complements_ = extant.complements_;
        this->sequence_ = extant.sequence_;
    }

    /**
     * C string contructor: Creates a sequence from a C string containing nucleotide characters.
     *
     * @param contents a C string containing nucleotide characters
     * @param complements a mapping of valid nucleotides to their complementary nucleotides
     * @throws std::domain_error for any string containing invalid nucleotide characters
     */
    Polynucleotide(const char *contents, std::map<char, char> complements) {
        this->complements_ = complements;
        this->operator+=(contents);  // reuse compound assignment/addition function
    }

    /**
     * Initializer-list constructor: Creates a sequence from an initializer_list of characters.
     *
     * @param list a list of nucleotide characters
     * @param complements a mapping of valid nucleotides to their complementary nucleotides
     * @throws std::domain_error if any element in the list is an invalid nucleotide character
     */
    Polynucleotide(std::initializer_list<char> list, std::map<char, char> complements) {
        this->complements_ = complements;
        for (char nucleotide : list)
            this->operator+=(nucleotide);  // reuse compound assignment/addition function
    }

    /**
     * Template sequence contructor: Creates a sequence from an existing sequence object.
     *
     * @tparam Sequence iterable sequence type containing characters e.g. std::string/std::list<char>
     * @param contents a sequence containing nucleotide characters
     * @param complements a mapping of valid nucleotides to their complementary nucleotides
     * @throws std::domain_error for any sequence containing invalid nucleotide characters
     */
    template <typename Sequence>
    Polynucleotide(const Sequence &contents, std::map<char, char> complements) {
        this->complements_ = complements;
        this->operator+=(contents);  // reuse compound assignment/addition function
    }

    /**
     * Initializer-list constructor: Creates a sequence from an initializer_list of sequences.
     * @tparam Sequence iterable sequence type containing characters e.g. std::string/std::list<char>
     *
     * @param list a list of sequences containing nucleotide characters
     * @param complements a mapping of valid nucleotides to their complementary nucleotides
     * @throws std::domain_error for any sequence containing invalid nucleotide characters
     */
    template <typename Sequence>
    Polynucleotide(std::initializer_list<Sequence> list, std::map<char, char> complements) {
        this->complements_ = complements;
        for (Sequence initial_sequence : list)
        this->operator+=(initial_sequence);  // reuse compound assignment/addition function
    }

    void insert(std::string::const_iterator __p, std::string::const_iterator __beg,
                std::string::const_iterator __end) {
        this->sequence_.insert(__p, __beg, __end);
    }

    void reserve(size_t new_cap) {
        sequence_.reserve(new_cap);
    }

    /**
     * Compound addition/assignment:
     * Appends valid nucleotide characters from a pre-existing Polynucleotide to this sequence.
     * @param appendage the sequence to append
     * @throws std::domain_error if the appendage has a different complement mapping
     */
    Polynucleotide &operator+=(const Polynucleotide &appendage) {
        if (this->complements_ != appendage.complements_)
            throw std::domain_error("Appendage has a different complement mapping");

        // Append the nucleotides
        auto seq = appendage.sequence_;
        this->insert(this->end(), seq.begin(), seq.end());

        return *this;
    }

    /**
     * Compound addition/assignment:
     * Appends valid nucleotide characters from a string to this sequence.
     * @param appendage the sequence to append
     * @throws std::domain_error if the appendage contains invalid characters
     */
    Polynucleotide &operator+=(const std::string &appendage) {
        for (char nucleotide : appendage)
            if (complements_.find(nucleotide) == complements_.end())
                throw std::domain_error("Appendage contains invalid characters");

        // Append the nucleotide characters to the current object
        sequence_.insert(sequence_.end(), appendage.begin(), appendage.end());
        return *this;
    }

    /**
     * Compound addition/assignment:
     * Appends valid nucleotide characters from a C string to this sequence.
     * @param appendage the sequence to append
     * @throws std::domain_error if the appendage contains invalid characters
     */
    Polynucleotide &operator+=(const char *appendage) {
        return *this += std::string(appendage);
    }

    /**
     * Compound addition/assignment: Appends one nucleotide character to this sequence.
     * @param nucleotide the character to append
     * @throws std::domain_error if nucleotide is an invalid character
     */
    Polynucleotide &operator+=(char nucleotide) {
        if (complements_.find(nucleotide) == complements_.end())
            throw std::domain_error("Invalid character");

        // Append the nucleotide
        sequence_.push_back(nucleotide);
        return *this;
    }

    /**
     * Compound multiplication/assignment:
     * Repeats/concatenates this sequence a number of times.
     *
     * @param repeat_count the number of times to repeat the sequence
     * @throws std::domain_error if repeat_count is negative
     */
    Polynucleotide &operator*=(int repeat_count) {
        *this = *this * repeat_count;
        return *this;
    }

    /**
     * const subscript: Returns the nucleotide at the given position.
     */
    char operator[](std::size_t pos) const {
        return this->sequence_[pos];
    }

    /**
     * Complement operator: Returns this sequence's complementary sequence.
     */
    Polynucleotide operator~() const {
        Polynucleotide complemented = *this;
        for (char &nucleotide : complemented.sequence_)
            nucleotide = complemented.complements_[nucleotide];

        return complemented;
    }

    /**
     * Unary minus operator: Returns this sequence in reverse.
     */
    Polynucleotide operator-() const {
        Polynucleotide reversed = *this;
        std::reverse(reversed.rbegin(), reversed.rend());
        return reversed;
    }

    /**
     * Addition operator: Returns this sequence concatenated with another.
     */
    Polynucleotide operator+(const Polynucleotide &that) const {
        Polynucleotide copy = *this;
        copy.sequence_.insert(copy.cend(), that.cbegin(), that.cend());
        return copy;
    }

    /**
     * Multiplication operator: Returns this sequence repeated/concatenated a number of times.
     *
     * @param repeat_count the number of times to repeat the sequence
     * @throws std::domain_error if repeat_count is negative
     */
    Polynucleotide operator*(int repeat_count) const {
        if (repeat_count < 0)
            throw std::domain_error("Repeat count cannot be negative");

        auto copy = *this;
        if (repeat_count == 0) {
            // maybe whipe the sequence?
            copy.clear();
            return copy;
        }
        copy.reserve(size() * repeat_count);

        for (int i = 1; i < repeat_count; i++)
            copy += *this;

        return copy;
    }

    /**
     * Assignment operator: Copies another polynucleotide's attributes to this object.
     */
    Polynucleotide &operator=(const Polynucleotide &that) {
        this->sequence_ = that.sequence_;
        this->complements_ = that.complements_;
        return *this;
    }

    /**
     * Logical equality:
     * Two Polynucleotide objects compare equal if they contain the same sequence of nucleotides.
     */
    bool operator==(const Polynucleotide &that) const {
        return this->sequence_ == that.sequence_;
    }

    /**
     * Stream insertion operator: object will appear as a plain string sequence, e.g. "GATTACA".
     */
    friend std::ostream &operator<<(std::ostream &out, const Polynucleotide &polynucleotide) {
        out << polynucleotide.sequence_;
        return out;
    }

    /**
     * Removes all elements from this sequence, resulting in an empty sequence.
     */
    void clear() {
        this->sequence_.clear();
    }

    /**
     * Returns a string containing this sequence's nucleotides.
     */
    std::string to_string() const {
        return this->sequence_;  // Will return a *copy* of our private, encapsulated string object
    }

    const char* to_c_string() const {
        return this->sequence_.c_str();
    }

    /**
     * Returns the length of this sequence.
     */
    std::size_t size() const {
        return this->sequence_.size();
    }

    /**
     * Sets the value of the nucleotide at the given position to the given value.
     * @param pos the position/index to set
     * @param nucleotide the new value for (*this)[pos]
     * @throws std::domain_error if nucleotide is an invalid character
     */
    void set(std::size_t pos, char nucleotide) {
        if (complements_.find(nucleotide) == complements_.end()) {
            throw std::domain_error("Invalid character");
        }

        this->sequence_[pos] = nucleotide;
    }

    /**
     * Returns a newly constructed sequence object with its value initialized to a copy of a
     * subsequence of this object. The substring is the portion of the object that starts at character
     * position pos and spans len characters (or until the end of the string, whichever comes first).
     * @param pos position of the first nucleotide to be copied as a subsequence. If this is equal to
     * the string length, the function returns an empty sequence. If this is greater than the string
     * length, it throws out_of_range. Note: The first nucleotide is denoted by a value of 0 (not 1).
     * @param len number of nucleotides to include in the subsequence (if the sequence is shorter, as
     * many nucleotides as possible are used).
     */
    Polynucleotide subsequence(std::size_t pos, std::size_t count) const {
        if (pos > size())
            throw std::out_of_range("Position is out of range");

        auto temp = *this;
        temp.sequence_ = sequence_.substr(pos, std::min(count, size() - pos));;

        return temp;
    }

    /**
     * Computes the Hamming distance between this sequence and another.
     * @param that the other sequence
     * @return the Hamming distance
     * @throws std::domain_error if the two sequences are of unequal length
     */
    int hamming_distance(const Polynucleotide &that) {
        if (this->size() != that.size())
            throw std::domain_error("Sequences are of unequal length");

        int distance = 0;

        // Compute the Hamming distance between the nucleotide sequences
        auto iter = sequence_.cbegin();
        auto that_iter = that.sequence_.cbegin();
        while (iter != sequence_.cend()) {
            if (*iter != *that_iter)
                distance++;

            ++iter;
            ++that_iter;
        }

        return distance;
    }

    /**
     * Returns a mapping of each unique nucleotide in the sequence to its frequency in the sequence.
     */
    std::map<char, int> nucleotide_counts() const {
        // create a map
        std::map<char, int> counts;
        for (auto nucleotide : complements_)
            counts[nucleotide.first] = 0;

        for (char nucleotide : sequence_)
            counts[nucleotide]++;

        return counts;
    }

 protected:
    std::map<char, char> complements_;  // use this for determining valid nucleotides and complements
    std::string sequence_;              // we'll store the actual nucleotide sequence here
};

}  // namespace cs19

#endif  // _CS19_POLYNUCLEOTIDE_H