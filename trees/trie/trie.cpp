/**
 * Pretty normal tree node
 * Uses an array of child pointers in heap
 */
template <typename K, typename D>
struct Trie<K,D>::Node
{
	Node** chdn;
	D data;
	bool used;
	inline Node(int numLets, Node* par) : used(0)
	{
		// Notably, we don't set data
		chdn = new Node*[numLets];
		for(int i = 0; i < numLets; ++i)
			chdn[i] = 0x0;
	}
};

/**
 * Standard constructor; takes in alphabet for trie
 * @param lets Alphabet of this tree
 * @param numLets Length of alphabet
 */
template <typename K, typename D>
Trie<K,D>::Trie(const K* lets, const int numLets)
{
	this->lets = new K[numLets];
	for(int i = 0; i < numLets; ++i)
		this->lets[i] = lets[i];
	this->numLets = numLets;
	this->root = 0x0;
	this->recursive = 0;
}

/**
 * Initializes root as root; declared as recursive
 * @param root Root of this trie
 * @param lets Alphabet of this tree
 * #param numLets Length of alphabet
 */
template <typename K, typename D>
Trie<K,D>::Trie(Node* root, const K* lets, const int numLets)
{
	this->lets = new K[numLets];
	for(int i = 0; i < numLets; ++i)
		this->lets[i] = lets[i];
	this->numLets = numLets;
	this->root = root;
	this->recursive = 1;
}

/**
 * Standard deconstructor; runs a DFS
 * Works through all children recursively
 */
template <typename K, typename D>
Trie<K,D>::~Trie()
{
	// Don't delete recursive objects
	if(this->recursive || !this->root)
		return;
	// DFS to delete everything
	for(int i = 0; i < numLets; ++i)
	{
		// Make a recursive object to delete
		Trie chd = Trie(this->root->chdn[i],
			this->lets, this->numLets);
		chd.recursive = 0;
	}
	// Delete and exit
	delete[] this->root->chdn;
	delete this->root;
}

/**
 * Runs a linear search of lets to find index
 * Throws if letter is not found
 * @param let Letter to index
 * @return Index of letter if found; else -1
 */
template <typename K, typename D>
int Trie<K,D>::index(const K& let) const
{
	// Just do a linear search through
	// A hashtable + binary search could make this log
	for(int i = 0; i < numLets; ++i)
		if(this->lets[i] == let)
			return i;
	throw std::range_error("index recieved invalid key");
}

/**
 * Returns the node closest to the given key
 * @param root Root to start searching from
 * @return Correct node if it exists; else 0x0
 */
template <typename K, typename D>
typename Trie<K,D>::Node* Trie<K,D>::clsNode(const K* key, const int keyLen) const
{
	// Run DFS on all branches
	Node* r = this->root;
	for(int i = 0; i < keyLen && r; ++i)
		r = r->chdn[this->index(key[i])];
	return r;
}

/**
 * Returns zero-indexed maximum depth
 * @return Zero-indexed depth of trie
 */
template <typename K, typename D>
int Trie<K,D>::depth() const
{
	// Empty trees are -1
	if(!this->root)
		return -1;
	// Find max depth among children
	int r = -1, d;
	for(int i = 0; i < this->numLets; ++i)
	{
		// Recursive call
		d = Trie(this->root->chdn[i],
			this->lets, this->numLets).depth();
		if(d > r)
			r = d;
	}
	// Return one more, for root
	return r+1;
}

/**
 * Inserts data at index
 * @param key Pointer to the key array
 * @param keyLen Length of the key array
 * @param data Data to place at key
 * @return If the node was inserted (vs. set)
 */
template <typename K, typename D>
bool Trie<K,D>::ins(const K* key, const int keyLen, const D& data)
{
	// Initialize the tree if necessary
	if(!this->root)
		this->root = new Node(this->numLets, 0x0);
	Node* par = 0x0;
	Node* chd = this->root;
	// Work down key until we have to start inserting
	int i = 0;
	for(; i < keyLen && chd; ++i)
	{
		par = chd;
		chd = chd->chdn[this->index(key[i])];
	}
	// We found it!
	if(chd)
	{
		// Attempt to insert here
		if(chd->used)
			return 0;
		chd->used = 1;
		chd->data = data;
		return 1;
	}
	// Start inserting nodes one back
	for(--i; i < keyLen; ++i)
	{
		// Make the node and iterate down
		par = (par->chdn[this->index(key[i])]
			= new Node(this->numLets, par));
	}
	// Now par is sitting at key
	par->used = 1;
	par->data = data;
	return 1;
}

/**
 * Deletes node at key and everything below, if possible
 * Throws error if key does not point to a used node
 * @param key Pointer to the key array
 * @param keyLen Length of the key array
 * @return Data stored at key
 */
template <typename K, typename D>
D Trie<K,D>::del(const K* key, const int keyLen)
{
	// We manually do a recursive search
	Node* nds[keyLen+1];
	int ids[keyLen+1];
	nds[0] = this->root;
	for(int i = 0; i < keyLen; ++i)
	{
		if(i < keyLen)
			ids[i] = this->index(key[i]);
		nds[i+1] = nds[i]->chdn[ids[i]];
		// Null?
		if(!nds[i+1])
			throw std::range_error("del received invalid key");
	}
	if(!nds[keyLen]->used)
		throw std::range_error("del recieved invalid key");
	// Are we deleting a branch?
	int cur = keyLen;
	bool needed = 0;
	for(int i = 0; i < this->numLets && !needed; ++i)
		if(nds[cur]->chdn[i])
			needed = 1;
	// There's something below---set to unused and exit
	if(needed)
	{
		nds[cur]->used = 0;
		return nds[cur]->data;
	}
	D r(nds[cur]->data);
	// Nothing below---work upwards until we can't
	while(!needed && cur)
	{
		// Delete and cut off
		delete nds[cur];
		if(cur > 0)
			nds[cur-1]->chdn[ids[cur-1]] = 0x0;
		else
			break;
		--cur;
		// Do we need this node?
		needed = nds[cur]->used;
		for(int i = 0; i < this->numLets && !needed; ++i)
			if(nds[cur]->chdn[i])
				needed = 1;
		// Go up if there is no need
	}
	return r;
}

/**
 * Standard contains method
 * @param key Key array to test
 * @param keyLen Length of key array
 * @return True iff the key is present
 */
template <typename K, typename D>
inline bool Trie<K,D>::contains(const K* key, const int keyLen) const
{
	// clsNode will return 0x0 if the node is not found
	Node* nd = this->clsNode(key, keyLen);
	return nd && nd->used;
}

/**
 * Standard get at index for a tree
 * Throws std::range_error if key is not present
 * @param key Key array to get
 * @param keyLen Length of key array
 * @return Data stored at key, by reference
 */
template <typename K, typename D>
inline D& Trie<K,D>::get(const K* key, const int keyLen) const
{
	// clsNode will return 0x0 if the node is not found
	Node* nd = this->clsNode(key, keyLen);
	if(!nd || !nd->used)
		throw std::range_error("get received invalid key");
	return nd->data;
}

/**
 * Standard set at index for a tree
 * Throws std::range_error if key is not present
 * @param key Key array to set
 * @param keyLen Length of key array
 * @param data Data to set key to
 */
template <typename K, typename D>
inline void Trie<K,D>::set(const K* key, const int keyLen, const D& data)
{
	// We could set unused nodes, but it doesn't feel like set
	Node* nd = this->clsNode(key, keyLen);
	if(!nd || !nd->used)
		throw std::range_error("set received invalid key");
	nd->data = data;
}

/**
 * Helper function for << operator
 * Uses DFS to print recursively
 * @param o Output stream to attach to
 * @param root Root of the printed tree
 * @param key Key used to get to this point
 * @param keyLen Length of key
 * @return New output stream
 */
template <typename K, typename D>
std::ostream& Trie<K,D>::printHelper(std::ostream& o, Node* root, K* key, int keyLen) const
{
	// Empty trees get to be sad
	if(!root)
		return o;
	// Print root
	for(int i = 0; i < keyLen; ++i)
		o << '\t';
	if(root->used)
		o << root->data;
	o << '[';
	for(int i = 0; i < keyLen; ++i)
		o << key[i];
	o << ']' << std::endl;
	// Now DFS
	for(int i = 0; i < this->numLets; ++i)
	{
		key[keyLen] = lets[i];
		this->printHelper(o, root->chdn[i],
			key, keyLen+1);
	}
	return o;
}

/**
 * Abbreviated tree output; calls printHelper
 * @param o Output stream to attach to
 * @param t Trie to print
 * @return New output stream
 */
template <typename K, typename D>
std::ostream& operator<<(std::ostream& o, const Trie<K,D>& t)
{
	K* key = new K[t.depth()+1];
	return t.printHelper(o, t.root, key, 0);
}
