/**
 * Pretty much a linked list
 * Stores both key and data values
 */
template <typename K, typename D>
struct HashTable<K,D>::Entry
{
	K key; D data;
	bool used;
	inline Entry() : used(0) {}
	inline Entry(const K& key, const D& data) : key(key), data(data), used(1) {}
};

/**
 * Pretty normal constructor for an array
 * @param size Size to set the array to
 */
template <typename K, typename D>
inline HashTable<K,D>::HashTable(int size)
{
	this->size = size;
	// Initialize table
	this->table = new Entry[size];
}

/**
 * Standard deconstructor
 * Goes through and deletes all linked lists
 */
template <typename K, typename D>
HashTable<K,D>::~HashTable()
{
	delete[] table;
}

/**
 * Helper method, finding closest position
 * Returns either entry with key or original entry
 * @param key Key to look for
 * @return Closest entry containing or available with key
 */
template <typename K, typename D>
int HashTable<K,D>::clsPos(const K& key) const
{
	// Initial guess
	int pos=this->hasher(key) % this->size, start=pos;
	Entry e = this->table[pos];
	// Linear probing
	while(!e.used || e.key != key)
	{
		pos = (pos+1) % this->size;
		// Have we checked everyone?
		if(pos == start)
			return pos;
		e = this->table[pos];
	}
	// For better or worse, return pos
	return pos;
}

/**
 * Inserts data into the table at key value
 * Uses chaining to resolve hash collisions
 * @param key Key to insert at
 * @param data Data to insert
 * @return Success
 */
template <typename K, typename D>
bool HashTable<K,D>::ins(const K& key, const D& data)
{
	// Because we look for unused, we need a different probe
	int pos=this->hasher(key) % this->size, start=pos;
	Entry e = this->table[pos];
	// Go until first available entry
	while(e.used)
	{
		if(e.key == key)
			return false;
		pos = (pos+1) % this->size;
		// Have we checked everywhere?
		if(start == pos)
			return false;
		e = this->table[pos];
	}
	// Set as reference variable and return
	Entry& toChange = this->table[pos];
	toChange.key = key; toChange.data = data; toChange.used = 1;
	return true;
}

/**
 * Deletes a key from the corresponding linked list
 * Throws an error if key is not present
 * @param key Key to delete
 * @return Data from deleted key
 */
template <typename K, typename D>
D HashTable<K,D>::del(const K& key)
{
	// Normal linear probing
	Entry& e = this->table[this->clsPos(key)];
	// Did we find it?
	if(!e.used || e.key != key)
		throw std::range_error("del received invalid key");
	// Simply set entry to unused
	e.used = 0;
	return e.data;
}

/**
 * Test if the key is in the hash table
 * @param key Key to test
 * @return True iff the key is in the table
 */
template <typename K, typename D>
bool HashTable<K,D>::contains(const K& key) const
{
	// Look for closest entry
	Entry e = this->table[this->clsPos(key)];
	// Did we find it?
	return e.used && e.key == key;
}

/**
 * Gets the table's value at key
 * Throws an error if the key is not present
 * @param key Key to search for
 * @return Data stored at key
 */
template <typename K, typename D>
D& HashTable<K,D>::operator[](const K& key) const
{
	// Look for closest entry
	int pos = this->clsPos(key);
	Entry& e = this->table[pos];
	// Did we find it?
	if(!e.used || e.key != key)
		throw std::range_error("[] received invalid key");
	return e.data;
}

/**
 * Alias to operator[]
 * @param key Key to search for
 * @return Data stored at key
 */
template <typename K, typename D>
D& HashTable<K,D>::get(const K& key) const
{
	return (*this)[key];
}

/**
 * Sets a key value to data
 * Basically calls []
 * @param key Key to set
 * @param data Data to set key to
 */
template <typename K, typename D>
inline void HashTable<K,D>::set(const K& key, const D& data)
{
	(*this)[key] = data;
}

/**
 * Outputs all nonempty linked lists
 * @param o Output stream to attach to
 * @param ht Hash table to print
 * @return New output stream
 */
template <typename KK, typename DD>
std::ostream& operator<<(std::ostream& o, const HashTable<KK,DD>& ht)
{
	// Loop through all entries
	for(int i = 0; i < ht.size; ++i)
	{
		// Loop through all entries
		typename HashTable<KK,DD>::Entry e = ht.table[i];
		if(!e.used)
			continue;
		o << e.data << '[' << e.key << ']' << std::endl;
	}
	return o;
}
