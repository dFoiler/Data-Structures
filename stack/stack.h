#ifndef _Stack_H_
#define _Stack_H_

template <typename T>
class Stack
{
	struct Node;

	Node* pTop;

	public:
		Stack();					// Construct stack
		~Stack();
		bool push(const T& inData);			// Add element to top of stack
		T pop();					// Return element at top of stack and remove from top
		T& top();					// Return element at top of stack
		bool empty();

	template <typename S>
	friend std::ostream& operator<< (std::ostream&, const Stack<S>&);
};

#include "stack.cpp"

#endif 		//_Stack_H_
