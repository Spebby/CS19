/**
 * @file linked_list_raw_pointers.h
 *
 * The beginnings of a doubly linked list class, using raw pointers.
 *
 * @author Thom Mott & Jeffrey Bergamini for CS 19m, jeffrey.bergamini@cabrillo.edu
 */
#ifndef LINKED_LIST_RAW_POINTERS_H_
#define LINKED_LIST_RAW_POINTERS_H_

#include <initializer_list>
#include <iostream>

namespace cs19 {

	/**
	 * Class LinkedList is an archetypal doubly linked list. The public API exposes some standard list
	 * operations. Node structures and internal list details are kept private.
	 *
	 * Also note that all member functions are defined inside the class declaration. (No separate .h and
	 * .cpp/.cc files.) Template classes are usually defined this way.
	 *
	 * @tparam T type of the list elements
	 */
	template <typename T>
	class LinkedList {
		struct Node;  // forward declaration for our private Node type

		public:
		LinkedList() {
			// N/A
		}
		LinkedList(const LinkedList& that) {
			auto node = that.head_;  // get a copy of the head_ pointer (increments head_'s reference count)
			while (node) {
				this->push_back(node->data);
				node = node->next;  // decrements ref count of current node, increments ref count of next node
			}
		}
		// Move constructor (used with std::move, e.g. new_list_var = std::move(old_list_var))
		LinkedList(const LinkedList&& that) : head_(that.head_), tail_(that.tail_), size_(that.size_) {
			// we have transferred another list's pointers to this list (and we now own them)
		}

		/** Constructs a list with a copy of each of the elements in `init_list`, in the same order. */
		LinkedList(std::initializer_list<T> list) {
			for (auto&& val : list)
				this->push_back(val);
			
			std::cerr << "List @ " << this << " (node size " << sizeof(Node)
					<< " bytes) has been constructed.\n";
		}

		/** Destroys each of the contained elements, and deallocates all memory allocated by this list. */
		//~LinkedList() {
			// This print statement is only for demo purposes! Rarely/never should this actually be here.
			//std::cerr << "List @ " << this << " (" << *this << ", " << this->size_ << " elements, "
			//		<< this->size_ * sizeof(Node) << " bytes total) is about to die.\n";
			// This is the actual destructor:
			// while (this->head_) {            // As long as we have a pointer to a head node...
			//   Node* old_head = this->head_;  // ...keep a copy of it...
			//   this->head_ = old_head->next;  // ...point the head at the next node instead...
			//   delete old_head;               // ...and delete the node that used to be the head.
			// }
		//}
		/** Appends a copy of `val` to this list. */
		void push_back(const T& val) {
			Node* new_node = new Node{val};  // Must eventually be deleted in the destructor!
			if (this->size_ == 0) {
			this->head_ = this->tail_ = new_node;
			} else {
			this->tail_->next = new_node;
			new_node->prev = this->tail_;
			this->tail_ = new_node;
			}
			++this->size_;
		}
		/**  Prepends a copy of `val` to this list. */
		void push_front(const T& val) {
			Node* new_node = new Node{val};  // Must eventually be deleted in the destructor!
			if (this->size_ == 0) {
				this->head_ = this->tail_ = new_node;
			} else {
				new_node->next = this->head_;
				this->head_->prev = new_node;
				this->head_ = new_node;
			}
			++this->size_;
		}
		
		/** Inserts this list into an ostream, with the format `[element1, element2, element3, ...]` */
		friend std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
			out << '[';
			// Technically we increment and decrement ref counts on each node as we traverse the list
			for (auto cur = list.head_; cur; cur = cur->next) {
			out << cur->data;
			if (cur->next)
				out << ", ";
			}
			out << ']';
			return out;
		}
		void push_back(T val) {
			// std::make_shared: alternative to std::shared_ptr<Node>(new Node(val))
			auto new_node = std::make_shared<Node>(val);
			if (this->size_ == 0) {
			this->head_ = this->tail_ = new_node;
			} else {
			this->tail_->next = new_node;
			new_node->prev = std::weak_ptr<Node>(this->tail_);
			this->tail_ = new_node;
			}
			++this->size_;
		}
		T pop_back() {
			T to_return = this->tail_->data;
			if (this->size_ == 1) {
			this->head_ = this->tail_ = nullptr;
			} else {
			this->tail_->prev.lock()->next = nullptr;  // weak_ptr::lock() promotes weak_ptr to shared_ptr
			this->tail_ = this->tail_->prev.lock();
			}
			--this->size_;
			return to_return;
		}
		std::size_t size() const {
			return this->size_;
		}

		private:
		struct Node {
			Node(T data) : data(data) {
			// N/A
			}
			// We can uncomment this to get some info on when nodes are automatically destroyed
			// ~Node() {
			//   std::cerr << "Node@" << this << " (" << this->data << ") has been destroyed\n";
			// }
			T data;
			std::shared_ptr<Node> next = nullptr;
			std::weak_ptr<Node> prev;
		};
		std::shared_ptr<Node> head_ = nullptr;
		std::shared_ptr<Node> tail_ = nullptr;
		std::size_t size_ = 0;
	};
}  // namespace cs19

#endif  // LINKED_LIST_RAW_POINTERS_H_