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
 * Returns the node closest to the given key
 * @param key Key to search through the tree with
 * @return Pointer to node containing the key
 */
template <typename K, typename D>
typename BinTree<K,D>::Node* BinTree<K,D>::clsNode(Node* root, const K key)
{
	// Does root exist?
	if(!root)
		return 0x0; // You made me do this
	// Now compare to root
	if(key < root->key) // To the left
	{
		// Is there a child there?
		if(!root->lft)
			// Good enough
			return root;
		// Recursive call
		return this->clsNode(root->lft, key);
	}
	if(key > root->key) // To the right
	{
		// Is there a child there?
		if(!root->rgt)
			// Good enough
			return root;
		// Recursive call
		return this->clsNode(root->rgt, key);
	}
	// Else this->root == key
	return root;
}

/**
 * Helper function, finding the successor of a node
 * Returns null if the given node is maximal
 * @param node Node to find the successor of
 * @return Null if node is maximal, otherwise successor
 */
template <typename K, typename D>
typename BinTree<K,D>::Node* BinTree<K,D>::sucNode(Node* node)
{
	Node* next(node);
	// Is there space to the right?
	if(node->rgt)
	{
		// Move one right and all the way left
		next = node->rgt;
		while(next->lft)
			next = next->lft;
		return next;
	}
	// Else we go up the tree until the key is bigger than the given
	while(next && next->key <= node->key)
		next = next->par;
	if(!next) // This was the maximum
		return 0x0;
	// Else we have a valid parent node bigger
	return next;
}

/**
 * Inserts into the binary tree
 * @param key Key of the inserted node
 * @param data Data to be stored in the inserted node
 * @return Success
 */
template <typename K, typename D>
bool BinTree<K,D>::ins(const K key, const D& data)
{
	Node* par = this->clsNode(this->root, key);
	// Was the tree empty?
	if(!par)
	{
		this->root = new Node(key, data, 0x0);
		return true;
	}
	// Now compare with parent
	if(key < par->key) // To the left
	{
		par->lft = new Node(key, data, par);
		return true;
	}
	if(key > par->key) // To the right
	{
		par->rgt = new Node(key, data, par);
		return true;
	}
	// Else the key has already been used
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
	Node* ret = this->clsNode(this->root, key);
	// Is there anything there?
	if(!ret)
		throw std::range_error("[] received empty tree");
	// Now compare with ret
	if(ret->key == key)
		return ret->data;
	// Else we failed to find the key no way we found the key
	throw std::range_error("[] received invalid key");
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
 * Returns the successor node
 * Throws an error if node is invalid or if node is max
 * @param key Key to walk with
 * @return Next key in the tree
 */
template <typename K, typename D>
inline K BinTree<K,D>::suc(const K key)
{
	// Get the needed node
	Node* cls = this->clsNode(this->root, key);
	if(cls->key != key)
		throw std::range_error("suc recieved invalid key");
	// Get the successor node
	Node* ret = this->sucNode(cls);
	if(!ret)
		throw std::range_error("suc received maximal key");
	return ret->key;
}

template <typename K, typename D>
D BinTree<K,D>::del(const K key)
{
	// Get the node
	Node* toDelete = this->clsNode(this->root, key);
	if(toDelete->key != key)
		throw std::range_error("del received invalid key");
	D r(toDelete->data);
	Node* toReplace = 0x0; // Assume no children
	// toDelete has two children
	if(toDelete->lft && toDelete->rgt)
	{
		// Replacement is successor; no left children
		toReplace = this->sucNode(toDelete);
		// Update replace relationships
		if(toReplace->rgt)
			toReplace->rgt->par = toReplace->par;
		// These concern rgt of toDelete or par of toReplace
		if(toReplace->par != toDelete)
		{
			if(toReplace->rgt)
				toReplace->rgt->par = toDelete->par;
			// No left children, so right child can sub in
			toReplace->par->lft = toReplace->rgt;
			toReplace->rgt = toDelete->rgt;
			toDelete->rgt->par = toReplace;
		}
		// These always need to change
		toReplace->par = toDelete->par;
		toReplace->lft = toDelete->lft;
		toDelete->lft->par = toReplace;
	}
	// toDelete has one child
	else if(toDelete->lft || toDelete->rgt)
	{
		// Replacement is the child
		toReplace = toDelete->lft ? toDelete->lft : toDelete->rgt;
		// Update replace relationships
		toReplace->par = toDelete->par;
	}
	// Change toDelete relationships
	if(toDelete == this->root)
		this->root = toReplace;
	else if(toDelete == toDelete->par->lft)
		toDelete->par->lft = toReplace;
	else
		toDelete->par->rgt = toReplace;
	// Delete and exit
	delete toDelete;
	return r;
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
	// Anti-segfault
	if(!bt.root)
		return o;
	// Output data, key, and parent key in order
	o << bt.root->data << '[' << bt.root->key << "]{";
	if(bt.root->par) o << bt.root->par->key;
	o << "} (";
	// Recursive calls to subtrees
	if(bt.root->lft)
		o << BinTree<K,D>(bt.root->lft);
	o << ") (";
	if(bt.root->rgt)
		o << BinTree<K,D>(bt.root->rgt);
	return o << ')';
}
