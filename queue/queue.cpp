#include "queue.h"

template <typename T>
struct Queue<T>::Node
{
	T data;
	Node* fwd;
	
	inline Node() : data(0x0), fwd(0x0) {}
	inline Node(T data, Node* fwd) : data(data), fwd(fwd) {}
};

template <typename T>
Queue<T>::Queue()
{
	this->beg = this->end = 0x0;
}

template <typename T>
Queue<T>::~Queue()
{
	while(this->beg)
	{
		Node* oldBeg = this->beg;
		this->beg = this->beg->fwd;
		delete oldBeg;
	}
}

template <typename T>
void Queue<T>::enqueue(const T& data)
{
	if(!this->beg)
	{
		beg = end = new Node(data, 0x0);
		return;
	}
	Node* newEnd = new Node(data, 0x0);
	this->end->fwd = newEnd;
	this->end = newEnd;
}

template <typename T>
T Queue<T>::dequeue()
{
	if(!this->beg)
		return NULL;
	Node* oldBeg = this->beg;
	T r(oldBeg->data);
	this->beg = this->beg->fwd;
	delete oldBeg;
	return r;
}

template <typename T>
T Queue<T>::top()
{
	return this->beg->data;
}

template <typename T>
std::ostream& operator<< (std::ostream& o, const Queue<T>& q)
{
	for(typename Queue<T>::Node* p = q.beg; p; p = p->fwd)
		o << p->data << '\t';
	return o;
}
