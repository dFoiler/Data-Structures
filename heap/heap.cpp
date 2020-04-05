/**
 * Standard constructor; builds array of specified size
 * @param size Maximum size of heap
 */
template <typename K>
inline Heap<K>::Heap(const int size)
{
	this->size = size;
	this->array = new K[size];
	this->next = 0;
}

/**
 * Standard deconstructor; destroys the allocated array
 */
template <typename K>
inline Heap<K>::~Heap()
{
	delete[] this->array;
}

/**
 * Inserts element into the heap via sift-up
 * @param key Key to insert
 * @return Success
 */
template <typename K>
bool Heap<K>::ins(const K key)
{
	// Is there space?
	if(this->next >= this->size)
		return false;
	// Place the key
	int i = this->next;
	this->array[i] = key;
	// Compare with parent of i: (i-1)/2
	while(i > 0 && this->array[(i-1)/2] < key)
	{
		// Exchange
		this->array[i] = this->array[(i-1)/2];
		this->array[(i-1)/2] = key;
		i = (i-1)/2;
	}
	// Successful placement
	++ this->next;
	return true;
}

/**
 * Pops off the top element and then sifts down
 * Throws std::range_eror if heap is empty
 * @return Element popped
 */
template <typename K>
K Heap<K>::del()
{
	// Heap is empty
	if(!this->next)
		throw std::range_error("del received empty heap");
	// Store our return
	K r = this->array[0];
	// Promote child up
	this->array[0] = this->array[this->next-1];
	--this->next;
	int key = this->array[0]; // Buffer variable
	int i = 0, replace;
	bool notBoth; // If we test both children
	// Sift down
	while(2*i+1 < next)
	{
		notBoth = 2*i+2 > next;
		// Are we in position?
		if(key > this->array[2*i+1] && (notBoth || key > this->array[2*i+2]))
			break;
		// Else swap with larger child
		replace = 2*i+2;
		if(notBoth || this->array[2*i+1] > this->array[2*i+2])
			replace = 2*i+1;
		this->array[i] = this->array[replace];
		this->array[replace] = key;
		// Continue
		i = replace;
	}
	return r;
}

/**
 * Peeks at the maximum element
 * @return Top of the heap
 */
template <typename K>
inline K Heap<K>::peek() const
{
	return this->array[0];
}

/**
 * Helper function for operator<<
 * @param o Output stream to attach to
 * @param depth Current depth in printing
 * @param child Status of root (left/right/root child)
 * @return New output stream
 */
template <typename K>
std::ostream& Heap<K>::printHelper(std::ostream& o, int index, int depth, char* path, char child) const
{
	// Degenerate base case
	if(index >= this->next) return o;
	// Right child
	path[depth] = '1';
	this->printHelper(o, 2*index+2, depth+1, path, '/');
	// Root
	path[depth] = 0x0;
	for(int i = 0; i < depth; ++i)
	{
		// Vertical bars added if we left-right or right-left
		if(i > 0 && path[i-1] != path[i])
			o << '|';
		o << '\t';
	}
	o << ' ' << child << ' ';
	o << this->array[index] << std::endl;
	// Left child
	path[depth] = '0';
	this->printHelper(o, 2*index+1, depth+1, path, '\\');
	return o;
}

/**
 * Output operator for bintree; calls printHelper
 * @param o Output stream to attach to
 * @param h Heap to print
 * @return New output stream
 */
template <typename K>
std::ostream& operator<<(std::ostream& o, const Heap<K>& h)
{
	// Compute maximum depth
	int d = 0;
	while(1 << (d++) < h.size);
	// Call printHelper
	char path[d];
	return h.printHelper(o, 0, 0, path, '-');
}
