/**
 * Pretty much a linked list
 * Stores both key and data values
 */
template <typename K, typename D>
struct HashTable<K,D>::Entry
{
	K key; D data;
	Entry* fwd;
	inline Entry(const K& key, const D& data) : key(key), data(data), fwd(0x0) {}
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
	this->table = new Entry*[size];
	for(int i = 0; i < size; ++i)
		this->table[i] = 0x0;
}

/**
 * Standard deconstructor
 * Goes through and deletes all linked lists
 */
template <typename K, typename D>
HashTable<K,D>::~HashTable()
{
	for(int i = 0; i < size; ++i)
	{
		// Pick up entries and next
		Entry* cur = this->table[i];
		Entry* next = cur->fwd;
		while(cur)
		{
			// Delete and iterate
			delete cur;
			cur = next;
			next = cur->fwd;
		}
	}
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
	Entry* toAdd = new Entry(key, data);
	// Check the hashed value
	int pos = this->hasher(key) % this->size;
	Entry* node = this->table[pos];
	// table is empty there
	if(!node)
	{
		this->table[pos] = toAdd;
		return true;
	}
	// Keep going until there's an empty spot
	if(node->key == key)
		return false;
	while(node->fwd)
	{
		node = node->fwd;
		if(node->key == key)
			return false;
	}
	// Set and return
	node->fwd = new Entry(key, data);
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
	// Looking for the parent node
	int pos = this->hasher(key) % this->size;
	Entry* par = this->table[pos];
	if(!par)
		throw std::range_error("del received invalid key");
	// Our key is right here!
	if(par->key == key)
	{
		D r(par->data);
		this->table[pos] = par->fwd;
		delete par;
		return r;
	}
	// Keep looking
	while(par->fwd && par->fwd->key != key)
		par = par->fwd;
	if(!par->fwd)
		throw std::range_error("del received invalid key");
	// Now par->fwd has the right key; update relationships and exit
	Entry* node = par->fwd;
	D r(node->data);
	par->fwd = node->fwd;
	delete node;
	return r;
}

/**
 * Test if the key is in the hash table
 * @param key Key to test
 * @return True iff the key is in the table
 */
template <typename K, typename D>
bool HashTable<K,D>::contains(const K& key) const
{
	// Look for the right node
	Entry* node = this->table[this->hasher(key) % this->size];
	while(node && node->key != key)
		node = node->fwd;
	// Abuse C++ type coercion
	return node;
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
	// Look for the right node
	Entry* node = this->table[this->hasher(key) % this->size];
	// Keep going until we find it
	while(node && node->key != key)
		node = node->fwd;
	if(!node)
		throw std::range_error("[] received invalid key");
	return node->data;
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
void HashTable<K,D>::set(const K& key, const D& data)
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
	// Loop through all lists
	for(int i = 0; i < ht.size; ++i)
	{
		// Loop through all entries
		typename HashTable<KK,DD>::Entry* e = ht.table[i];
		if(!e)
			continue;
		o << '[' << e->data << '[' << e->key << ']';
		while(e = e->fwd)
			o << ", " << e->data << '[' << e->key << ']';
		o << ']' << std::endl;
	}
	return o;
}
