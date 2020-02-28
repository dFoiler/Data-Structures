template <typename K, typename D>
struct BinTree<K,D>::Node
{
	K key; D data;
	Node *lft, *rgt, *par;
	
	inline Node() : key(0x0), data(0x0), lft(0x0), rgt(0x0), par(0x0) {}
	inline Node(K key, D data, Node* par) : key(key), data(data), lft(0x0), rgt(0x0), par(par) {}
};

template <typename K, typename D>
inline BinTree<K,D>::BinTree()
{
	this->root = 0x0;
	this->recursive = false;
}

template <typename K, typename D>
inline BinTree<K,D>::BinTree(Node* root)
{
	this->root = root;
	// These are private objects creted for recursion
	this->recursive = true;
}

template <typename K, typename D>
BinTree<K,D>::~BinTree()
{
	// There's nothing here to delete
	if(!this->root || this->recursive) // Don't delete temp objects
		return;
	// Create stack objects that will be recursively deleted automatically
	BinTree rgt(this->root->rgt); rgt.recursive = false;
	BinTree lft(this->root->lft); lft.recursive = false;
	// Now delete the current pointer
	delete this->root;
}

template <typename K, typename D>
bool BinTree<K,D>::insert(const K key, const D& data)
{
	// Is there anything there?
	if(!this->root)
	{
		this->root = new Node(key, data, 0x0);
		return true;
	}
	// Now compare to root
	if(key < this->root->key) // To the left
	{
		// Is there a child there?
		if(this->root->lft)
			// Recursive call
			return BinTree<K,D>(this->root->lft).insert(key, data);
		// Make the child
		this->root->lft = new Node(key, data, this->root);
		return true;
	}
	if(key > this->root->key) // To the right
	{
		// Is there a child there?
		if(this->root->rgt)
			// Recursive call
			return BinTree<K,D>(this->root->rgt).insert(key, data);
		// Make the child
		this->root->rgt = new Node(key, data, this->root);
		return true;
	}
	// Else key == this->root->key, so we can't add the key in!
	return false;
}

template <typename K, typename D>
D& BinTree<K,D>::operator[](const K key)
{
	// Is there anything there?
	if(!this->root)
	{
		std::cerr << "Empty tree" << std::endl;
		std::exit(-1);
	}
	// Now compare with root
	if(key < this->root->key) // To the left
	{
		if(!this->root->rgt) // Nothing's there
			return this->root->data; // Good enough
		// Recursive call
		return BinTree<K,D>(this->root->rgt)[key];
	}
	if(key > this->root->key) // To the right
	{
		if(!this->root->lft) // Nothing's there
			return this->root->data; // Good enough
		// Recursive call
		return BinTree<K,D>(this->root->lft)[key];
	}
	// Finally, we have found our key
	return this->root->data;
}

template <typename K, typename D>
inline D& BinTree<K,D>::get(const K key)
{
	return (*this)[key];
}

template <typename K, typename D>
std::ostream& operator<<(std::ostream& o, const BinTree<K,D>& bt)
{
	o << '(' << bt.root->data << '[' << bt.root->key << "] ";
	if(bt.root->lft)
		o << BinTree<K,D>(bt.root->lft);
	o << ' ';
	if(bt.root->rgt)
		o << BinTree<K,D>(bt.root->rgt);
	o << ')';
	return o;
}
