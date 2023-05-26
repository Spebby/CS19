/**
 * @file cs19_compact_string_set.cpp
 *
 * A first-draft implementation of our specialized string set.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */
#include "cs19_compact_string_set.h"
#include <string>
 
namespace cs19 {
    void CompactStringSet::insert(const std::string& value) {
        Node* cur = &this->root_;                          // Start at the dummy "root" node.
        for (auto character : value) {                     // For each character...
            Node* search = this->find_next(cur, character);  // ... find a child containing the character.
            if (search) {                                    // If such a node exists...
                cur = search;                                // ... nothing to do. We just move on.
            } else {                                         // ... otherwise, we need to insert a new node.
                Node* new_node = new Node{character};
                if (cur->child) {    // This node already has a child...
                    cur = cur->child;  // ... so its child needs a sibling.
                    while (cur->sibling)
                    cur = cur->sibling;     // Find the last sibling...
                    cur->sibling = new_node;  // ... and give it a new sibling.
                } else {
                    cur->child = new_node;  // This node is childless. Let's give it one.
                }
                cur = new_node;
            }
        }
        if (!cur->terminal) {    // If the stopping point was not already marked as terminal...
            ++this->num_strings_;  // ... we inserted a new string
            cur->terminal = true;  // ... and the stopping point needs to be marked as such.
        }
    }
    
    bool CompactStringSet::contains(const std::string& value) const {
        const Node* cur = &this->root_;           // Start at the dummy "root" node.
        for (auto character : value) {            // For each character...
            cur = this->find_next(cur, character);  // ... find a child of this node containing the char
            if (!cur)
            return false;  // ... otherwise, this string must not be in the set
        }
        return cur->terminal;  // This set contains the string if the last char was marked as terminal
    }
    
    // Returns any child or sibling node representing the given char, or nullptr if none.
    CompactStringSet::Node* CompactStringSet::find_next(const Node* base, char to_find) const {
        // If the node has a child...
        if (base->child) {
            // ... maybe the child has a matching char
            if (base->child->letter == to_find)
                return base->child;
            // ... or maybe one of their siblings does
            Node* sibling = base->child->sibling;
            while (sibling) {
                if (sibling->letter == to_find)
                    return sibling;
                sibling = sibling->sibling;
            }
        }
        return nullptr;  // No match found
    }
}  // namespace cs19