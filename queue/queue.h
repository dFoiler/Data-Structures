#include <iostream>

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
		T dequeue();
		T top();
	
	template <typename S>
	friend std::ostream& operator<< (std::ostream&, const Queue<S>&);
};
