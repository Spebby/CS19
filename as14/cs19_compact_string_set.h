/**
 * @file cs19_compact_string_set.h
 *
 * A first-draft interface of our specialized string set. No destructor yet.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */
#ifndef CS19_COMPACT_STRING_SET_H_
#define CS19_COMPACT_STRING_SET_H_
 
#include <string>
#include <vector>
 
namespace cs19 {
/**
 * Class CompactStringSet represents a set of strings in a structure that is potentially more space-
 * and time-efficient than std::set<std::string>.
 */
class CompactStringSet {
    // Our internal element type (see diagrams from lecture)
    struct Node {
        char letter;              // each node stores a letter
        bool terminal = false;    // ... and is potentially the end of a string in the set
        Node* sibling = nullptr;  // ... and may have "sibling" node(s) that also follow previous letter
        Node* child = nullptr;    // ... and may have a "child" node for the next letter in a string
    };

 public:
    /**
     * Inserts a string into this set, if not already present.
     *
     * @param value the string to insert
     * @return whether the string was inserted (i.e., whether it was a new addition to the set)
     */
    bool insert(const std::string& value);
    /**
     * Searches this set for a given string.
     *
     * @param the string to search for
     * @return whether the string exists in this set
     */
    bool contains(const std::string& value) const;
    /**
     * Removes a string from this set, if present. Deleting subsequently unused nodes is optional.
     *
     * @param value the string to remove
     * @return whether the string had been present in the set
     */
    bool erase(const std::string& value);
    /**
     * Returns the number of strings in this set.
     */
    std::size_t size() const {
        return this->num_strings_;
    }
    /**
     * Returns an iterator to the first element of the set. A CompactStringSet makes no guarantees
     * as to which specific string is considered its first element. But, in any case, the range
     * begin() to end() covers all the strings in the set.
     * If the set is empty, the returned iterator will be equal to end(). 
     */
    auto begin();
    /**
     * Returns an iterator to the element following the last element of the set.
     * This element acts as a placeholder; attempting to access it results in undefined behavior. 
     */
    auto end();
    /**
     * Returns the closest n strings to the given string, in "autocomplete" fashion. Proximity shall
     * be measured as follows: A child node is the closest to a given node, and any of its siblings
     * are the next closest, in order of their sibling links.
     *
     * @param base the string from which to suggest autocompletions
     * @param n the maximum number of autocompletions to return
     * @return at most n autocompletions of the base, in descending order of proximity from the base
     */
    std::vector<std::string> autocomplete(const std::string& base, std::size_t n) const;
    
 private:
    Node root_{0};                 // A dummy node for the starting point of the set
    std::size_t num_strings_ = 0;  // The number of strings in the set
    Node* find_next(const Node* base, char to_find) const;  // Returns matching child or sibling node
};

}  // namespace cs19

#endif