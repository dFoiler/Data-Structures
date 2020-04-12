#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error
#include <string>	// std::string
#include <sstream>	// std::stringstream

/**
 * Linked list class, with mostly standard methods.
 * Author: Nir Elber
 */
template <typename T>
class LinkedList
{
	public:
		LinkedList();
		// Constructs length to have the right number of objects
		LinkedList(int len);
		// Copy-constructor
		LinkedList(const LinkedList& list);
		// Creates an alias
		LinkedList& operator=(const LinkedList& rhs);
		LinkedList(const T* tArray, const int& len);
		~LinkedList();
		inline void clear();
		bool isEmpty() const;
		// Some standard stuff
		bool operator==(const LinkedList& rhs) const;
		bool equals(const LinkedList& rhs) const;
		bool operator!=(const LinkedList& rhs) const;
		// Standardly returns size
		int size() const;
		// Array access
		T& operator[](const int& idx) const;
		inline T& get(const int& idx) const;
		inline void set(const int& idx, const T& val);
		// Adds an element to the end of the list
		void add(const T& val);
		// Inserts so that (*this)[idx] = val
		void add(const T& val, const int& idx);
		// Demonic list-adding functions
		LinkedList& link(const LinkedList& rhs);
		LinkedList& operator+(const LinkedList& rhs);
		LinkedList& operator+=(const LinkedList& rhs);
		// Deleting; return by value not reference
		T del(const int& idx);
		// Standard swap of nodes
		void swap(const int& idx1, const int& idx2);
		// Exchange the values stored
		void exchg(const int& idx1, const int& idx2);
		// Standard algorithms
		int find(const T& val) const;
		int rfind(const T& val) const;
		bool contains(const T& val) const;
		LinkedList& subList(const int& start, const int& len) const;
		void sort();
		void reverse();
		// Because why not
		std::string toString() const;
	private:
		struct Node;
		// These are the key privates
		Node* head;
		int len;
		// Retrieve the node just before index
		Node* nodeJustBefore(const int& idx) const;
		// Swap two forward pointers; used for swap
		inline void swapFwds(Node* n1, Node* n2);
		// Outputting
		template <typename TT>
		friend std::ostream& operator<<(std::ostream& o, const LinkedList<TT>& list);
};

#include "linkedlist.cpp"

#endif // LINKEDLIST_H
