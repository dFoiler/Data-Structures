#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error

template <typename K>
class Heap
{
	private:
		int size;
		K* array;
		int next;
		std::ostream& printHelper(std::ostream&, int, int, char*, char) const;
	public:
		Heap(const int size);
		~Heap();
		bool ins(const K key);
		K del();
		inline K peek() const;
	template <typename KK>
	friend std::ostream& operator<< (std::ostream& o, const Heap<KK>& h);
};

#include "heap.cpp"
