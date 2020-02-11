#include "priorityqueue.h"

/**
 * Standard linked list node
 */
template <typename T>
struct PQueue<T>::Node
{
	T data;
	int priority;
	Node *fwd;
	
	inline Node() : data(0x0), fwd(0x0), priority(0) {}
	inline Node(T data, Node* fwd, int priority) : data(data), fwd(fwd), priority(priority) {}
};

/**
 * Standard default constructor
 * Sets pointers to null
 */
template <typename T>
PQueue<T>::PQueue()
{
	this->beg = this->end = 0x0;
}

/**
 * Standard deconstructor
 */
template <typename T>
PQueue<T>::~PQueue()
{
	// Loop through all elements
	while(this->beg)
	{
		// Extract the elment we need, update beg, and delete it
		Node* oldBeg = this->beg;
		this->beg = this->beg->fwd;
		delete oldBeg;
	}
}

/**
 * Enqueues data onto the queue
 * Inserts by (min) priority at the end, in O(n) time
 * @param data Data to enqueue
 * @param priority Priority of input data
 */
template <typename T>
void PQueue<T>::enqueue(const T& data, const int priority)
{
	// Does the list exist?
	if(!this->beg)
	{
		// Okay, then initialize beg and end to a new element
		beg = end = new Node(data, 0x0, priority);
		return;
	}
	// Find who is our predecessor
	// Are we better than the first?
	if(priority < this->beg->priority)
	{
		// We have to update beg
		this->beg = new Node(data, this->beg, priority);
		return;
	}
	// Else loop until the next element is worse
	Node* bck = this->beg; // Element before current node
	while(bck->fwd && bck->fwd->priority <= priority)
		bck = bck->fwd;
	// Create the new node and upadte relationships
	Node* newNode = new Node(data, bck->fwd, priority);
	bck->fwd = newNode;
	// Update the end if the new node is at the end
	if(!newNode->fwd)
		this->end = newNode;
}

/**
 * Equivalent to enqueue
 * @param data Data to enqueue
 * @param priority Priority of input data
 */
template <typename T>
inline void PQueue<T>::push(const T& data, const int priority)
{
	this->enqueue(data, priority);
}

/**
 * Dequeues data from the queue
 * @return Value of data stored
 */
template <typename T>
T PQueue<T>::dequeue()
{
	// If there is no list, return nothing
	if(!this->beg)
		return NULL;
	// Extract the beginning, and move it along
	Node* oldBeg = this->beg;
	T r(oldBeg->data);
	this->beg = this->beg->fwd; // Continuous dequeuing makes beg 0x0 eventually
	// We don't need this anymore
	delete oldBeg;
	return r;
}

/**
 * Equivalent to dequeue
 * @return Value of data stored
 */
template <typename T>
inline T PQueue<T>::pop()
{
	return this->dequeue();
}

/**
 * Returns the top element, by reference
 * @return Data stored in the first-queued element
 */
template <typename T>
T& PQueue<T>::top()
{
	return this->end->data;
}

/**
 * Standard output for the queue
 * @param o Output stream to write to
 * @param q Queue to write
 * @return Updated output stream
 */
template <typename T>
std::ostream& operator<< (std::ostream& o, const PQueue<T>& q)
{
	for(typename PQueue<T>::Node* p = q.beg; p; p = p->fwd)
		o << p->data << " [" << p->priority << ']' << '\t';
	return o;
}
