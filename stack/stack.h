#include <iostream>
#include <stdexcept>

template <typename T>
class Stack
{
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
