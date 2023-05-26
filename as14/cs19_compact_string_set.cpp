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
    bool CompactStringSet::insert(const std::string& value) {
        Node* cur = &this->root_;                          // Start at the dummy "root" node.
        bool newStringInserted = false; // Flag to track if the string was inserted as a new string
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
                newStringInserted = true; // We inserted a new string
            }
        }
        if (!cur->terminal) {    // If the stopping point was not already marked as terminal...
            ++this->num_strings_;  // ... we inserted a new string
            cur->terminal = true;  // ... and the stopping point needs to be marked as such.
            newStringInserted = true; // We inserted a new string
        }

        return newStringInserted;
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

    bool CompactStringSet::erase(const std::string& value) {
        Node* cur = &this->root_; // Start at the dummy "root" node.
        Node* prev = nullptr; // Pointer to the previous node.
        Node* target = nullptr; // Pointer to the node containing the last character of the value.
        // Traverse the tree to find the node containing the last character of the value.
        for (auto character : value) {
            Node* search = this->find_next(cur, character);
            if (!search) {
                return false;  // The value is not present in the set, return false.
            }
            prev = cur;
            cur = search;
        }

        // Check if the last node of the value is marked as terminal.
        if (!cur->terminal) {
            return false;  // The value is not present in the set, return false.
        }

        // Unmark the last node as terminal.
        cur->terminal = false;
        --this->num_strings_;  // Decrement the count of strings.

        // Traverse back from the last node to the root and delete unused nodes if required.
        while (cur != &this->root_ && cur->child == nullptr && cur->sibling == nullptr) {
            if (prev->child == cur) {
                prev->child = nullptr;  // Set the child pointer of the previous node to nullptr.
            } else {
                prev->sibling = nullptr;  // Set the sibling pointer of the previous node to nullptr.
            }

            delete cur;  // Delete the current node.
            cur = prev;
            prev = find_parent(cur, value);  // Find the parent node of the current node.
        }

        return true;  // The value was present in the set and has been successfully erased, return true.
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