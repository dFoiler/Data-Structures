#include "queue.h"

/**
 * Standard linked list node
 */
template <typename T>
struct Queue<T>::Node
{
	T data;
	Node *fwd;
	
	inline Node() : data(0x0), fwd(0x0) {}
	inline Node(T data, Node* fwd) : data(data), fwd(fwd) {}
};

/**
 * Standard default constructor
 * Sets pointers to null
 */
template <typename T>
Queue<T>::Queue()
{
	this->beg = this->end = 0x0;
}

/**
 * Standard deconstructor
 */
template <typename T>
Queue<T>::~Queue()
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
 * @param data Data to enqueue
 */
template <typename T>
void Queue<T>::enqueue(const T& data)
{
	// Does the list exist?
	if(!this->beg)
	{
		// Okay, then initialize beg and end to a new element
		beg = end = new Node(data, 0x0);
		return;
	}
	// Tack a new element onto the end
	Node* newEnd = new Node(data, 0x0);
	this->end->fwd = newEnd;
	this->end = newEnd;
}

/**
 * Equivalent to enqueue
 * @param data Data to enqueue
 */
template <typename T>
void Queue<T>::push(const T& data)
{
	this->enqueue(data);
}

/**
 * Dequeues data from the queue
 * @return Value of data stored
 */
template <typename T>
T Queue<T>::dequeue()
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
T Queue<T>::pop()
{
	return this->dequeue();
}

/**
 * Returns the top element, by reference
 * @return Data stored in the first-queued element
 */
template <typename T>
T& Queue<T>::top()
{
	return this->beg->data;
}

/**
 * Standard output for the queue
 * @param o Output stream to write to
 * @param q Queue to write
 * @return Updated output stream
 */
template <typename T>
std::ostream& operator<< (std::ostream& o, const Queue<T>& q)
{
	for(typename Queue<T>::Node* p = q.beg; p; p = p->fwd)
		o << p->data << '\t';
	return o;
}
