#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error

template <typename K>
class Heap
{
	private:
		int size;
		int* array;
		int next;
	public:
		Heap(const int size);
		~Heap();
		bool ins(const K key);
		K del();
		inline K peek();
	template <typename KK>
	friend std::ostream& operator<< (std::ostream& o, const Heap<KK>& h);
};

#include "heap.cpp"
