/**
 * Standard binary search tree node
 * Includes left, right, and parent
 */
template <typename K, typename D>
struct BinTree<K,D>::Node
{
	K key; D data;
	Node *lft, *rgt, *par;
	
	inline Node() : key(0x0), data(0x0), lft(0x0), rgt(0x0), par(0x0) {}
	inline Node(K key, D data, Node* par) : key(key), data(data), lft(0x0), rgt(0x0), par(par) {}
};

/**
 * Standard default constructor
 * Sets root to null and makes the object nonrecursive
 */
template <typename K, typename D>
inline BinTree<K,D>::BinTree()
{
	this->root = 0x0;
	this->recursive = false;
}

/**
 * Initializes a tree with given root, declared as recursive
 * @param root The root of this tree
 */
template <typename K, typename D>
inline BinTree<K,D>::BinTree(Node* root)
{
	this->root = root;
	// These are private objects creted for recursion
	this->recursive = true;
}

/**
 * Typical deconstructor
 * Makes left and right child trees and recursively deletes
 */
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

/**
 * Inserts into the binary tree
 * @param key Key of the inserted node
 * @param data Data to be stored in the inserted node
 * @return Success
 */
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

/**
 * Array-like access by reference
 * Throws an error if the tree is empty or for invalid index
 * @param key Key of data to look for
 * @return Data of the given key
 */
template <typename K, typename D>
D& BinTree<K,D>::operator[](const K key)
{
	// Is there anything there?
	if(!this->root)
		throw std::range_error("tree is empty");
	// Now compare with root
	if(key < this->root->key) // To the left
	{
		// Recursive call if possible
		if(this->root->rgt)
			return BinTree<K,D>(this->root->rgt)[key];
	}
	if(key > this->root->key) // To the right
	{
		// Recursive call if possible
		if(this->root->lft)
			return BinTree<K,D>(this->root->lft)[key];
	}
	if(key == this->root->key) // Got it!
		return this->root->data;
	// Else we failed to find the key no way we found the key
	throw std::range_error("invalid index");
}

/**
 * Identical to array access
 * @param key Key of data to look for
 * @return Data of the given key
 */
template <typename K, typename D>
inline D& BinTree<K,D>::get(const K key)
{
	return (*this)[key];
}

/**
 * Output operator for bintree
 * Uses nested parantheses to denote parent-child relationships
 * @param o Output stream to attach to
 * @param bt Binary tree to print
 */
template <typename K, typename D>
std::ostream& operator<<(std::ostream& o, const BinTree<K,D>& bt)
{
	o << '(' << bt.root->data << '[' << bt.root->key << "] ";
	if(bt.root->lft)
		o << BinTree<K,D>(bt.root->lft);
	o << ' ';
	if(bt.root->rgt)
		o << BinTree<K,D>(bt.root->rgt);
	return o << ')';
}
