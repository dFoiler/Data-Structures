/**
 * Pretty normal tree node
 * Uses an array of child pointers in heap
 */
template <typename K, typename D>
struct Trie<K,D>::Node
{
	Node* par;
	Node** chdn;
	D data;
	bool used;
	inline Node(int numLets, Node* par) :
		par(par), used(0)
	{
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
Trie<K,D>::Trie(const K* lets, const int& numLets)
{
	this->lets = new K[numLets];
	for(int i = 0; i < numLets; ++i)
		this->lets[i] = lets[i];
	this->numLets = numLets;
	this->root = new Node(numLets, 0x0);
	this->recursive = 0;
}

/**
 * Initializes root as root; declared as recursive
 * @param root Root of this trie
 */
template <typename K, typename D>
Trie<K,D>::Trie(Node* root, const K* lets, const int& numLets)
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
	delete this->root->chdn;
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
	for(int i = 0; i < numLets; ++i)
		if(this->lets[i] == let)
			return i;
	throw std::range_error("index recieved invalid key");
}

/**
 * Returns the node closest to the given key
 * @param root Root to start searching from
 * 
 */
template <typename K, typename D>
typename Trie<K,D>::Node* Trie<K,D>::clsNode(const K* key, const int& keyLen) const
{
	// No tree to search through?
	if(!this->root)
		return 0x0;
	Node* par = 0x0;
	Node* chd = this->root;
	for(int i = 1; i < keyLen && chd; ++i)
	{
		par = chd;
		chd = par->chds[this->index(key[i])];
	}
	return par;
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
	int r = -1;
	for(int i = 0; i < this->numLets; ++i)
	{
		// Recursive call
		int d = Trie(this->root->chdn[i],
			this->lets, this->numLets).depth();
		r = r > d ? r : d;
	}
	// Return one more, for root
	return r+1;
}

/**
 * Inserts data at index
 * @param key Pointer to the key array
 * @param keyLen Length of the key array
 * @param data Data to place at key
 * @return If the node was inserted
 */
template <typename K, typename D>
bool Trie<K,D>::ins(const K* key, const int& keyLen, const D& data)
{
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
		chd->used = 1;
		chd->data = data;
		return 0;
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

template <typename K, typename D>
std::ostream& Trie<K,D>::printHelper(std::ostream& o, Node* root, K* key, int keyLen) const
{
	// Empty trees get to be sad
	if(!root)
		return o;
	// Print root
	for(int i = 0; i < keyLen; ++i)
		o << '|' << '\t';
	if(root->used)
		o << this->root->data;
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

template <typename K, typename D>
std::ostream& operator<<(std::ostream& o, const Trie<K,D>& t)
{
	K* key = new K[t.depth()+1];
	return t.printHelper(o, t.root, key, 0);
}
