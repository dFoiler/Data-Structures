/**
 * Fake tree node struct; has par
 * Has no complex maintanence methods
 */
template <typename K, typename D>
struct BTree<K,D>::Node
{
	Node** chdn;
	Node* par;
	K* keys; int numKeys;
	D* data;
	inline Node(const int m, Node* par) : par(par), numKeys(0)
	{
		chdn = new Node*[m];
		for(int i = 0; i < m; ++i)
			chdn[i] = 0x0;
		keys = new K[m-1];
		data = new D[m-1];
	}
};

/**
 * Initializes as an m-ary tree
 * @param m Maximum number of children per node
 */
template <typename K, typename D>
BTree<K,D>::BTree(const int m)
{
	this->root = 0x0;
	this->m = m;
	this->recursive = 0;
}

/**
 * Initializes recursive tree
 * @param root Root of recursive tree
 * @param m Maximum number of children per node
 */
template <typename K, typename D>
BTree<K,D>::BTree(Node* root, const int m)
{
	this->root = root;
	this->m = m;
	// Object is recursive
	this->recursive = 1;
}

/**
 * Standard deconstructor for a tree
 * Uses DFS to delete everything
 */
template <typename K, typename D>
BTree<K,D>::~BTree()
{
	// Ignore empty  and recursive trees
	if(!this->root && !this->recursive)
		return;
	// DFS to delete all children
	for(int i = 0; i < m; ++i)
	{
		BTree bt(this->root->chdn[i], m);
		bt.recursive = 0;
	}
	// Now delete root pointers
	delete[] this->root->chdn;
	delete[] this->root->keys;
	delete[] this->root->data;
	delete this->root;
}

/**
 * Lower-bounds the index of a key in a node
 * @param nd Node to search through
 * @param key Key to search with
 * @return Index of the key in the node
 */
template <typename K, typename D>
int BTree<K,D>::index(Node* nd, const K& key) const
{
	// Binary search through the array
	int lo=-1, hi=nd->numKeys, mid;
	// hi fails
	while(lo < hi-1)
	{
		mid = (lo+hi)/2;
		if(key < nd->keys[mid])
			hi = mid;
		else
			lo = mid;
	}
	return lo;
}

/**
 * Returns node containing key or leaf where key goes
 * @param key Key to search with
 * @return Pointer to desired node
 */
template <typename K, typename D>
typename BTree<K,D>::Node* BTree<K,D>::clsNode(const K& key) const
{
	Node* par = 0x0;
	Node* cur = this->root;
	// Iterate down through the tree
	while(cur)
	{
		// Look for key
		int lo = this->index(cur, key);
		// We found it!
		if(cur->keys[lo] == key)
			return cur;
		// Otherwise go down
		else
		{
			par = cur;
			cur = cur->chdn[lo+1];
		}
	}
	// If we hit a null early, use previous
	return par;
}

template <typename K, typename D>
void BTree<K,D>::insAt(const K& key, const D& data, Node* nd, Node* rChd)
{
	std::cout << "Inserting : " << data << '[' << key << ']';
	if(nd)
		std::cout << " with " << nd->data[0] << '[' << nd->keys[0] << ']';
	//if(rChd)
	//	std::cout << std::endl << "rChd : " << std::endl << BTree(rChd, this->m);
	std::cout << std::endl << "Current : " << std::endl << *this << std::endl;
	// At root? Push tree upwards
	if(!nd)
	{
		Node* rt = new Node(this->m, 0x0); rt->numKeys = 1;
		rt->keys[0] = key; rt->data[0] = data;
		rChd->par = this->root->par = rt;
		rt->chdn[1] = rChd; rt->chdn[0] = this->root;
		this->root = rt;
		return;
	}
	// Shift nd to make space for key
	int lo = this->index(nd, key);
	K lastKey(nd->keys[this->m-2]); D lastDat(nd->data[this->m-2]);
	Node* lastChd(nd->chdn[this->m-1]);
	for(int i = nd->numKeys < this->m ? nd->numKeys : this->m-1;
		i > lo+1; --i)
	{
		nd->keys[i] = nd->keys[i-1];
		nd->data[i] = nd->data[i-1];
		nd->chdn[i+1] = nd->chdn[i];
	}
	if(lo+1 < this->m-1) // Space?
	{
		nd->keys[lo+1] = key;
		nd->data[lo+1] = data;
		nd->chdn[lo+2] = rChd; // left child is lo+1
		if(rChd) rChd->par = nd;
	}
	else
	{
		lastKey = key; lastDat = data; lastChd = rChd;
	}
	++nd->numKeys;
	if(nd->numKeys < this->m) // Space?
		return;
	// Splitting time --- make new right child
	Node* nrChd = new Node(this->m, nd->par);
	nd->numKeys = nd->numKeys/2;
	K mK = nd->keys[nd->numKeys]; // nd's sibling is right of median
	D mD = nd->data[nd->numKeys];
	nrChd->numKeys = this->m-1 - nd->numKeys;
	for(int i = 0; i < nrChd->numKeys-1; ++i)
	{
		nrChd->keys[i] = nd->keys[i+nd->numKeys+1];
		nrChd->data[i] = nd->data[i+nd->numKeys+1];
		nrChd->chdn[i] = nd->chdn[i+nd->numKeys+1];
	}
	nrChd->keys[nrChd->numKeys-1] = lastKey;
	nrChd->data[nrChd->numKeys-1] = lastDat;
	nrChd->chdn[nrChd->numKeys] = lastChd;
	this->insAt(mK, mD, nd->par, nrChd);
}

/**
 * Inserts data at key
 */
template <typename K, typename D>
bool BTree<K,D>::ins(const K& key, const D& data)
{
	std::cout << "-------------------------" << std::endl;
	// Empty tree case
	if(!this->root)
	{
		this->root = new Node(this->m, 0x0);
		this->root->keys[0] = key;
		this->root->data[0] = data;
		this->root->numKeys = 1;
		return 1; 
	}
	// Find closest node for insertion
	Node* nd = this->clsNode(key);
	K k(key); D d(data);
	int lo = this->index(nd, key);
	if(nd->keys[lo] == key)
		return 0;
	// Shift to make space
	this->insAt(key, data, nd, 0x0);
	return 1;
}

template <typename K, typename D>
std::ostream& BTree<K,D>::printHelper(std::ostream& o, Node* root, const int depth) const
{
	// Ignore empty tree
	if(!root)
		return o;
	// Output with DFS
	for(int i = 0; i < root->numKeys; ++i)
	{
		// Output child
		this->printHelper(o, root->chdn[i], depth+1);
		// Output separator node
		for(int s = 0; s < depth; ++s)
			o << '|' << '\t';
		o << root->data[i] << '[' << root->keys[i] << ']';
		o << '{';
		if(root->par)
			std::cout << root->par->data[0] << '[' << root->par->keys[0] << ']';
		o << '}' << std::endl;
	}
	// Output last child
	return this->printHelper(o, root->chdn[root->numKeys], depth+1);
}

template <typename K, typename D>
std::ostream& operator<<(std::ostream& o, const BTree<K,D>& bt)
{
	return bt.printHelper(o, bt.root, 0);
}
