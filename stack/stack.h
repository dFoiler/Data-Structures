#ifndef STACK_H
#define STACK_H

#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error

template <typename T>
class Stack
{
	private:
		struct Node;
		Node* pTop;

	public:
		Stack();
		~Stack();
		bool push(const T& inData);
		T pop();
		T& top() const;
		bool empty() const;

	template <typename S>
	friend std::ostream& operator<< (std::ostream&, const Stack<S>&);
};

#include "stack.cpp"

#endif // STACK_H
