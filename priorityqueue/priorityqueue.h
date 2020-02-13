#include <iostream>

template <typename T>
class PQueue
{
	private:
		struct Node;
		Node* beg;
		Node* end;
	public:
		PQueue();
		~PQueue();
		void enqueue(const T& in, const int priority);
		inline void push(const T& in, const int priority);
		T dequeue();
		inline T pop();
		T& top();
	
	template <typename S>
	friend std::ostream& operator<< (std::ostream&, const PQueue<S>&);
};

#include "priorityqueue.cpp"
