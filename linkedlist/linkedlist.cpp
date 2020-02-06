#ifndef LL_H
#define LL_H
#include "linkedlist.h"
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#include <sstream>
#endif

/**
 * The internal node struct behind the linked list.
 * It acts like a struct, so that's what it's called.
 */
template <typename T>
struct LinkedList<T>::Node
{
	T val;
	Node* fwd;

	inline Node() : fwd(0x0) {}
	inline Node(T val) : val(val) {}
	inline Node(T val, Node* fwd) : val(val), fwd(fwd) {}
};

/** 
 * Standard default constructor, setting everything to 0.
 */
template <typename T>
LinkedList<T>::LinkedList() : head(0x0), len(0) {}

/**
 * Constructor setting length.
 * Initializes empty nodes in the heap.
 * @param len Desired length.
 */
template <typename T>
LinkedList<T>::LinkedList(int len)
{
	this->len = len;
	if(len <= 0)
	{
		this->head = 0x0;
		return;
	}
	// Otherwise we go through and create all the space
	this->head = new Node(*(new T()), new Node());
	Node* current = this->head;
	for(int i = 1; i < len; ++i)
	{
		// Set fwd and iterate
		current->fwd = new Node(*(new T()), new Node());
		current = current->fwd;
	}
}

/**
 * Copy-constructor.
 * Makes a copy in the heap.
 * @param list List to copy.
 */
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	this->len = list.len;
	if(this->len == 0)
	{
		this->head = 0x0;
		return;
	}
	// Set first element via head
	this->head = new Node(list.head->val);
	// Iterate down list
	Node* current = this->head;
	Node* toAdd = list.head->fwd;
	for(int i = 1; i < this->len; ++i)
	{
		// Create the new node
		current->fwd = new Node(toAdd->val);
		current = current->fwd;
		toAdd = toAdd->fwd;
	}
	// Set the last one to null
	current->fwd = 0x0;
}

/**
 * Assignment operator, creating an alias without destroying this (rule of 3).
 * this is not destroyed in case the object should be in use after.
 * @param list List to alias.
 */
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list)
{
	this->head = list.head;
	this->len = list.len;
	return *this;
}

/**
 * Essentially a copy-constructor from an array.
 * @param tArray Pointer to array of objects of T type.
 * @param len Length of array to copy.
 */
template <typename T>
LinkedList<T>::LinkedList(const T* tArray, const int& len)
{
	this->len = len;
	if(this->len == 0)
	{
		this->head = 0x0;
		return;
	}
	// Append the first
	this->head = new Node(tArray[0]);
	// Now iterate
	Node* current = this->head;
	for(int i = 1; i < this->len; ++i)
	{
		// Create the new node and iterate
		current->fwd = new Node(tArray[i]);
		current = current->fwd;
	}
	// Set the last one to null
	current->fwd = 0x0;
}

/**
 * Standard destructor, destroying all nodes in the process.
 * It goes until null is found in case length has been corrupted for some reason.
 */
template <typename T>
LinkedList<T>::~LinkedList()
{
	// Iterate down the list
	Node* nextToDelete;
	for(Node* toDelete = this->head; toDelete;)
	{
		// Store where we're going
		nextToDelete = toDelete->fwd;
		// Delete current node
		delete toDelete;
		// Iterate
		toDelete = nextToDelete;
	}
	this->len = 0;
}

/**
 * Clears the linked list.
 * Just calls the destructor and default constructor.
 */
template <typename T>
inline void LinkedList<T>::clear()
{
	this->~LinkedList();
	LinkedList();
}

/**
 * Tests if the list is empty by checking if this->head is null.
 * A length check could work, but this aligns with printing.
 * @return 1 if this->head is null, 0 if not.
 */
template <typename T>
inline bool LinkedList<T>::isEmpty()
{
	return !this->head;
}

/**
 * Standard node-by-node equality checker.
 * @param rhs List on the right-hand side of the expression.
 * @return 1 if the lists are equal, 0 if not.
 */
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs)
{
	// Run length checking
	if(this->len != rhs.len)
		return false;
	// Iterate down the two lists
	Node* currentLHS = this->head;
	Node* currentRHS = rhs.head;
	// With no reason to use one iterator over the other, take the neutral option.
	for(int i = 0; i < this->len; ++i)
	{
		// Test values
		if(currentLHS->val != currentRHS->val) // Aha!
			return false;
		// Now iterate
		currentLHS = currentLHS->fwd;
		currentRHS = currentRHS->fwd;
	}
	return true;
}

/**
 * Equality check by calling operator==.
 * @param rhs List to be compared to.
 * @return 1 if the lists are equal, 0 if not.
 */
template <typename T>
inline bool LinkedList<T>::equals(const LinkedList<T>& rhs)
{
	return (*this)==rhs;
}

/**
 * Not equal check to round out the equality check.
 * Implemented as not operator==.
 * @param rhs List on the right-hand side of the expression.
 * @return 0 if the lists are equal, 1 if not.
 */
template <typename T>
inline bool LinkedList<T>::operator!=(const LinkedList<T>& rhs)
{
	return !((*this)==rhs);
}

/**
 * Returns the length of the list.
 * @return The length of the list, passed by value.
 */
template <typename T>
inline int LinkedList<T>::size()
{
	return this->len;
}

/**
 * Standard array access.
 * Returns by reference to allow for list[0] = 5 statements.
 * Does not catch idx = len as an issue and will seg fault.
 * @param idx Index to access.
 * @return Value of the node at index, passed by reference.
 */
template <typename T>
inline T& LinkedList<T>::operator[](const int& idx)
{
	// Call nodeJustBefore if nonzero, in which case there should be something before.
	if(idx)
		return this->nodeJustBefore(idx)->fwd->val;
	return this->head->val;
}

/**
 * Get method for an index. Identical to operator[].
 * @param idx Index to access.
 * @return Value of the node at index, passed by reference.
 */
template <typename T>
inline T& LinkedList<T>::get(const int& idx)
{
	return (*this)[idx];
}

/**
 * Set method for an index. Returns void by default.
 * @param idx Index to access.
 * @param val Desired value for the node at that index.
 */
template <typename T>
inline void LinkedList<T>::set(const int& idx, const T& val)
{
	(*this)[idx] = val;
}

/**
 * Inserts val so that (*this)[idx] is set to val.
 * @param val Value to place at the end of the list.
 * @param idx Index of node to place val into.
 */
template <typename T>
void LinkedList<T>::add(const T& val, const int& idx)
{
	// Is there something before to update?
	if(idx)
	{
		// Retrieve the element just before
		Node* before = this->nodeJustBefore(idx);
		// Insert the new node with the correspdonding relationships
		before->fwd = new Node(val, before->fwd);
	}
	else
		// Otherwise we add to the start; create the new head
		this->head = new Node(val, this->head);
	// Success
	++(this->len);
}

/**
 * Appends an element to the end of the list with the other add.
 * @param val Value to place at the end of the list.
 */
template <typename T>
inline void LinkedList<T>::add(const T& val)
{
	this->add(val, this->len);
}

/**
 * Links two linked lists together, without making copies.
 * @param rhs List to link to the end of *this.
 * @return *this, now containing rhs at the end. By reference.
 */
template <typename T>
LinkedList<T>& LinkedList<T>::link(const LinkedList<T>& rhs)
{
	// Get last node and update relationships
	// There's something after the head
	if(this->head)
		this->nodeJustBefore(this->len)->fwd = rhs.head;
	// this is empty
	else
		this->head = rhs.head;
	// Success
	this->len += rhs.len;
	return *this;
}

/**
 * Adds two linked lists together, making copies of each in the heap.
 * @param rhs List on the right-hand side of the expression.
 * @return A new list containing lhs linked with rhs. By reference.
 */
template <typename T>
inline LinkedList<T>& LinkedList<T>::operator+(const LinkedList<T>& rhs)
{
	// Create copy
	LinkedList& r1 = *(new LinkedList(*this));
	// Call the other method
	return r1 += rhs; // r1 is on the heap; no destructor?
}

/**
 * Adds a copy of the other list to this.
 * @param rhs List on the right-hand side of the expression.
 * @return Returns *this, passed by reference.
 */
template <typename T>
inline LinkedList<T>& LinkedList<T>::operator+=(const LinkedList<T>& rhs)
{
	// Create a copy list and link
	return this->link( *(new LinkedList(rhs)) );
}

/**
 * Deletes an element and returns the value just deleted.
 * There shouldn't be a reason to alter the value afterwards, so it's passed by value.
 * @param idx Index to be deleted.
 * @return Value of the node that was just deleted.
 */
template <typename T>
T LinkedList<T>::del(const int& idx)
{
	Node* current;
	// No element before?
	if(idx)
	{
		// Retrieve the element just before
		Node* before = this->nodeJustBefore(idx);
		current = before->fwd;
		// Update relationship
		before->fwd = current->fwd;
	}
	else
	{
		current = this->head;
		// Update relationship
		this->head = current->fwd;
	}
	// Store value about to be deleted
	T r(current->val);
	// Now delete it
	delete current;
	// Success
	--(this->len);
	return r;
}

/**
 * Swaps two nodes without copying values.
 * Efficient if the data type is large.
 * @param idx1 First index of nodes to swap.
 * @param idx2 Second index of nodes to swap.
 */
template <typename T>
void LinkedList<T>::swap(const int& idx1, const int& idx2)
{
	// Hooray do nothing
	if(idx1 == idx2) return;
	// Recursive call so that I only have to test idx1 == 0
	if(idx2 < idx1)
		return this->swap(idx2, idx1);
	// Make the before
	Node* bck2 = this->nodeJustBefore(idx2);
	// There is something before idx1
	if(idx1)
	{
		// Else there is something before it to update
		Node* bck1 = this->nodeJustBefore(idx1);
		// bck1 -> now2 -> fwd1
		// bck2 -> now1 -> fwd2
		// Exchange bck and now forward pointers
		swapFwds(bck1, bck2);
		swapFwds(bck1->fwd, bck2->fwd);
		return;
	}
	// Else idx1 is the head.
	// We could just make a dummy node point to this->head
	// Running manually is a bit faster, albeit more instruction
	Node* now2 = bck2->fwd;
	// Update relationships doing manual swaps
	bck2->fwd = this->head;
	swapFwds(now2, bck2->fwd);
	// Update location of head
	this->head = now2;
	return;
	
}

/**
 * Exchanges the data stored in two nodes.
 * Efficient if the data type is small.
 * @param idx1 First index of nodes to exchange.
 * @param idx2 Second index of nodes to exchange.
 */
template <typename T>
void LinkedList<T>::exchg(const int& idx1, const int& idx2)
{
	// Extract the corresponding nodes, careful with 0
	Node* now1 = this->nodeJustBefore(idx1);
	if(idx1) now1 = now1->fwd;
	Node* now2 = this->nodeJustBefore(idx2);
	if(idx2) now2 = now2->fwd;
	// Now run the swap with a temp; no xor because of no T ^ T
	T temp(now1->val);
	now1->val = now2->val;
	now2->val = temp;
	return;
}

/**
 * A linear-time forward search for a value.
 * @param val Value being searched for in the list.
 * @return Index of first node storing val if one exists; -1 if not.
 */
template <typename T>
int LinkedList<T>::find(const T& val)
{
	// Itearte down the list
	Node* current = this->head;
	for(int r = 0; r < this->len; ++r)
	{
		// If found, return directly
		if(current->val == val)
			return r;
		current = current->fwd;
	}
	return -1;
}

/**
 * A linear-time reverse search for a value.
 * @param val Value being searched for in the list.
 * @return Index of last node storing val if one exists; -1 if not.
 */
template <typename T>
int LinkedList<T>::rfind(const T& val)
{
	int r = -1;
	// Iterate down the list
	Node* current = this->head;
	for(int i = 0; i < this->len; ++i)
	{
		// If found, simply update r
		if(current->val == val)
			r = i;
		current = current->fwd;
	}
	// Returns last found occurrence
	return r;
}

/**
 * Copies a sublist between the specified indices into the heap.
 * If the length is longer than it should be, this will be interpreted as memory corruption and seg fault.
 * @param start Index to start the sublist.
 * @param len Length of the sublist.
 * @return The desired segment of the list, passed by reference.
 */
template <typename T>
LinkedList<T>& LinkedList<T>::subList(const int& start, const int& len)
{
	// Extract node just before, being careful about 0
	Node* thisCurrent = this->head;
	if(start)
		thisCurrent = this->nodeJustBefore(start)->fwd;
	// Create a dummy list
	LinkedList<T> dummy;
	dummy.head = thisCurrent; dummy.len = len;
	// Now we call the copy-constructor to give us our list
	LinkedList<T>* r = new LinkedList(dummy); // Heap avoids destructor
	// We set dummy to look newly instantiated because it's about to get destroyed as we exit scope
	dummy.head = 0x0; dummy.len = 0;
	return *r;
}

/**
 * A somewhat streamlined recursive implementation of merge sort.
 * Sorts in ascending order.
 */
template <typename T>
void LinkedList<T>::sort()
{
	// The stupid base case
	if(this->len < 2) return;
	// Copy the lists into two halves
	LinkedList<T> lists[2] = {this->subList(0, this->len/2), this->subList(this->len/2, this->len - this->len/2)};
	// Recusrive sort
	lists[0].sort(); lists[1].sort();
	// It's merge time
	// Store nodes and indices
	Node* listNodes[2] = {lists[0].head, lists[1].head};
	Node* thisNode = this->head;
	// Now iterate down
	{
		bool toTake;
		while(listNodes[0] && listNodes[1])
		{
			// Take the smaller side
			toTake = listNodes[0]->val > listNodes[1]->val;
			// Copy the value
			thisNode->val = listNodes[toTake]->val;
			// Iterate
			thisNode = thisNode->fwd;
			listNodes[toTake] = listNodes[toTake]->fwd;
		}
	}
	// Now throw in everything else
	for(char whichList = 0; whichList < 2; ++whichList)
		while(listNodes[whichList])
		{
			thisNode->val = listNodes[whichList]->val;
			thisNode = thisNode->fwd;
			listNodes[whichList] = listNodes[whichList]->fwd;
		}
}

/**
 * Reverses the linked list in linear time.
 */
template <typename T>
void LinkedList<T>::reverse()
{
	// Stupid case
	if(this->len < 2) return;
	// Else make three pointers in trio
	Node* bck = 0x0;
	Node* now = this->head;
	Node* fwd = now->fwd;
	// Iterate
	while(fwd)
	{
		// Change now to point backwards
		now->fwd = bck;
		// Update the three pointers
		bck = now;
		now = fwd;
		fwd = fwd->fwd;
	}
	// We ended one step early: now is the last, so now->fwd should be bck, which is unupdated
	now->fwd = bck;
	// Update the head
	this->head = now;
}

/**
 * Standard outputting of the linked list, with pythonic syntax.
 * @param o Output stream to append to.
 * @param list The list being printed.
 * @return The output stream with the list appended.
 */
template <typename T>
std::ostream& operator<<(std::ostream& o, const LinkedList<T>& list)
{
	// Check if list is empty
	if(!list.len || !list.head)
		return o << '[' << ']';
	// And output each element:
	// First
	o << '[' << list.head->val;
	// Now iterate
	for(typename LinkedList<T>::Node* current = list.head->fwd;
		!current; current = current->fwd)
		o << ',' << ' ' << current->val;
	// Close bracket
	return o << ']';
}

/**
 * Standard toString method.
 * Calls the insertion operator to do the heavy lifting.
 * @return Desired ending string.
 */
template <typename T>
std::string LinkedList<T>::toString()
{
	// Check if list is empty
	if(!this->len || !this->head)
		return "[]";
	std::stringstream sstream;
	// And output each element:
	// First
	sstream << '[' << this->head->val;
	// Now iterate
	for(typename LinkedList<T>::Node* current = this->head->fwd;
		!current; current = current->fwd)
		sstream << ',' << ' ' << current->val;
	// Close bracket
	sstream << ']';
	return sstream.str();
}

/**
 * Swaps the forward pointers of two nodes.
 * A helper method for the swap function.
 * @param n1 Pointer to the first node to swap.
 * @param n2 Pointer to the second node to swap.
 */
template <typename T>
inline void LinkedList<T>::swapFwds(Node* n1, Node* n2)
{
	// Test for equality
	if(n1->fwd == n2->fwd)
		return;
	// Else run xor swap
	n1->fwd = (Node*)((long)n1->fwd ^ (long)n2->fwd);
	n2->fwd = (Node*)((long)n1->fwd ^ (long)n2->fwd);
	n1->fwd = (Node*)((long)n1->fwd ^ (long)n2->fwd);
}

/**
 * A surprisingly useful private method, returning the node before specified index.
 * Notably, nodeJustBefore(0) returns this->head.
 * Exits if index is invalid (negative or more than length).
 * @param idx Index directly after the desired node.
 * @return Pointer to node just before the specified index, except 0 returns this->head.
 */
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::nodeJustBefore(const int& idx)
{
	// Size check
	if(idx < 0 || idx > this->len)
	{
		std::cerr << "Invalid index caught in nodeJustBefore." << std::endl;
		std::exit(1);
	}
	// Just keep going until just before index
	Node* before = this->head;
	for(int j = 0; j < idx-1; ++j)
		before = before->fwd;
	return before;
}
