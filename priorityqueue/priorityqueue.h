#include <iostream>
#include <stdexcept>

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
		T& top() const;
	
	template <typename S>
	friend std::ostream& operator<< (std::ostream&, const PQueue<S>&);
};

#include "priorityqueue.cpp"
