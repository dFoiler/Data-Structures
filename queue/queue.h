#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error

template <typename T>
class Queue
{
	private:
		struct Node;
		Node* beg;
		Node* end;
	public:
		Queue();
		~Queue();
		void enqueue(const T& in);
		void push(const T& in);
		T dequeue();
		T pop();
		T& top() const;
	
	template <typename S>
	friend std::ostream& operator<< (std::ostream&, const Queue<S>&);
};

#include "queue.cpp"

#endif // QUEUE_H
