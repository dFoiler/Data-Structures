#include <iostream>

/**
 * Fairly standard linked list node
 */
template <typename T>
struct Stack<T>::Node
{
	T data;
	Node* next;

	inline Node() : data(0x0), next(0x0) {}
	inline Node(T data, Node* next) : data(data), next(next) {}
};

/** 
 * Standard default constructor
 */
template <typename T>
Stack<T>::Stack()
{
	pTop = 0x0;
}

/**
 * Standard deconstructor
 */
template <typename T>
Stack<T>::~Stack()
{
	// Loop through all elements in pTop
	while(this->pTop)
	{
		Node* oldTop = this->pTop;
		this->pTop = this->pTop->next;
		// Delete each
		delete oldTop;
	}
}

/**
 * Pushes an item to the top of the stack
 * @param data Object to put at the top
 * @return Success
 */
template <typename T>
bool Stack<T>::push(const T& data)
{
	// Set pTop to a node which had the data and points to pTop
	this->pTop = new Node(data, this->pTop);
	return true;
}
/**
 * Removes the top item of the stack and returns
 * @return The item that was just popped
 */
template <typename T>
T Stack<T>::pop()
{
	// Does the stack exist?
	if(!this->pTop)
		return NULL;
	// Get top node
	Node* oldTop = this->pTop;
	// Set new top node
	this->pTop = oldTop->next;
	// Now delete top and return data
	T data = oldTop->data;
	delete oldTop;
	return data;
}
/**
 * Returns the top item
 * @return The item pointed by pTop
 */
template <typename T>
T& Stack<T>::top()
{
	return pTop->data;
}

/**
 * Tests if the stack is empty
 * @return True if the top is null, 0 otherwise
 */
template <typename T>
bool Stack<T>::empty()
{
	return !pTop;
}

/**
 * Standard output for the stack
 * @param o Output stream to write to
 * @param s Stack to write
 * @return Updated output stream
 */
template <typename T>
std::ostream& operator<< (std::ostream& o, const Stack<T>& s)
{
	// Loop through all nodes
	for(typename Stack<T>::Node* p = s.pTop; p; p = p->next)
		// Print data at each node
		o << p->data << '\t';
	return o;
}
