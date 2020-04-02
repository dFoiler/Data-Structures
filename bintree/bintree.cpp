/**
 * Standard binary search tree node
 * Includes left, right, and parent
 */
template <typename K, typename D>
struct BinTree<K,D>::Node
{
	K key; D data;
	Node *lft, *rht, *par;
	
	inline Node() : key(0x0), data(0x0), lft(0x0), rht(0x0), par(0x0) {}
	inline Node(K key, D data, Node* par) : key(key), data(data), lft(0x0), rht(0x0), par(par) {}
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
	// These are private objects created for recursion
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
	BinTree rht(this->root->rht); rht.recursive = false;
	BinTree lft(this->root->lft); lft.recursive = false;
	// Now delete the current pointer
	delete this->root;
}

/**
 * Returns the node closest to the given key
 * @param root Root to start searching with
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
		if(!root->rht)
			// Good enough
			return root;
		// Recursive call
		return this->clsNode(root->rht, key);
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
	if(node->rht)
	{
		// Move one right and all the way left
		next = node->rht;
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
 * Computes and returns the size of the tree recursively
 * @return Number of nodes in the tree
 */
template <typename K, typename D>
int BinTree<K,D>::size()
{
	// Is there anything there?
	if(!this->root)
		return 0;
	// Recursive call
	return 1 + BinTree<K,D>(this->root->lft).size()
		+ BinTree<K,D>(this->root->rht).size();
}

/**
 * Computes and returns zero-indexed depth of a node
 * Throws an error if the node is not present
 * @param key Key to walk with
 * @return Zero-indexed depth of the key
 */
template <typename K, typename D>
int BinTree<K,D>::depth(const K key)
{
	// Find the correct node
	Node* cls = this->clsNode(this->root, key);
	if(!cls)
		throw std::range_error("depth received empty tree");
	if(key != cls->key)
		throw std::range_error("depth received invalid key");
	// Work up the tree to root
	int r = 0;
	while(cls->par)
	{
		cls = cls->par;
		++r;
	}
	return r;
}

/**
 * Computes and returns zero-indexed depth of the tree
 * Returns -1 if the tree is empty
 * @return Zero-indexed depth of tree
 */
template <typename K, typename D>
int BinTree<K,D>::depth()
{
	// Empty tree gives -1
	if(!this->root)
		return -1;
	// Run recursive calls
	int dLft = BinTree<K,D>(this->root->lft).depth();
	int dRht = BinTree<K,D>(this->root->rht).depth();
	return 1 + (dLft > dRht ? dLft : dRht);
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
	if(key == par->key)	// Key already in use
		return false;
	else if(key < par->key) // To the left
		par->lft = new Node(key, data, par);
	else			// To the right
		par->rht = new Node(key, data, par);
	return true;
}

/**
 * Deletes an element by key
 * Throws an error if the key is nonexistant
 * @param key Key of node to delete
 * @return Value stored in removed element
 */
template <typename K, typename D>
D BinTree<K,D>::del(const K key)
{
	// Get the node
	Node* toDelete = this->clsNode(this->root, key);
	if(!toDelete || toDelete->key != key)
		throw std::range_error("del received invalid key");
	D r(toDelete->data);
	Node* toReplace = 0x0; // Assume no children
	// toDelete has two children
	if(toDelete->lft && toDelete->rht)
	{
		// Replacement is successor; no left children
		toReplace = this->sucNode(toDelete);
		// Update replace relationships
		// These concern rgt of toDelete or par of toReplace
		if(toReplace->par != toDelete)
		{
			if(toReplace->rht) // Fixing that
				toReplace->rht->par = toReplace->par;
			// No left children, so right child can sub in
			toReplace->par->lft = toReplace->rht;
			toReplace->rht = toDelete->rht;
			toDelete->rht->par = toReplace;
		}
		// These always need to change
		toReplace->par = toDelete->par;
		toReplace->lft = toDelete->lft;
		toDelete->lft->par = toReplace;
	}
	// toDelete has one child
	else if(toDelete->lft || toDelete->rht)
	{
		// Replacement is the child
		toReplace = toDelete->lft ? toDelete->lft : toDelete->rht;
		// Update replace relationships
		toReplace->par = toDelete->par;
	}
	// Change toDelete parent relationships
	if(toDelete == this->root)
		this->root = toReplace;
	else if(toDelete == toDelete->par->lft)
		toDelete->par->lft = toReplace;
	else
		toDelete->par->rht = toReplace;
	// Delete and exit
	delete toDelete;
	return r;
}

/**
 * Checks if the tree contains given key
 * @param key Key to walk with
 * @return True iff key is present in tree
 */
template <typename K, typename D>
inline bool BinTree<K,D>::contains(const K key)
{
	Node* cls = this->clsNode(this->root, key);
	return cls && cls->key == key;
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

/**
 * Get the maximum key in the tree
 * Throws an error if given an empty tree
 * @return Maximum key
 */
template <typename K, typename D>
K BinTree<K,D>::max()
{
	Node* r = this->root;
	if(!r)
		throw std::range_error("max received empty tree");
	// Keep going right until done
	while(r->rht)
		r = r->rht;
	return r->key;
}

/**
 * Get the minimum key in the tree
 * Throws an error if given an empty tree
 * @return Minimum key
 */
template <typename K, typename D>
K BinTree<K,D>::min()
{
	Node* r = this->root;
	if(!r)
		throw std::range_error("min received empty tree");
	// Keep going left until done
	while(r->lft)
		r = r->lft;
	return r->key;
}

/**
 * Outputs the tree to an array of data sorted by key
 * Returns null on empty tree
 * @retrun Array of data sorted by key
 */
template <typename K, typename D>
D* BinTree<K,D>::toArray()
{
	if(!this->root)
		return 0x0;
	// Now fill in the array
	D* r = new D[this->size()];
	int curIndex = -1;
	// Get minimum node and successor down
	for(Node* cur = this->clsNode(this->root, this->min());
		cur; cur = this->sucNode(cur))
		// Set and iterate
		r[++curIndex] = cur->data;
	return r;
}

/**
 * Helper function for operator<<
 * @param o Output stream to attach to
 * @param depth Current depth in printing
 * @param child Status of root (left/right/root child)
 * @return New output stream
 */
template <typename K, typename D>
std::ostream& BinTree<K,D>::printHelper(std::ostream& o, int depth, char child)
{
	// Degenerate base case
	if(!this->root) return o;
	// Right child
	BinTree(this->root->rht).printHelper(o,depth+1,'/');
	// Root
	for(int i = 0; i < depth; ++i)
		o << '\t';
	o << child << ' ';
	o << this->root->data << '[' << this->root->key << ']' << std::endl;
	// Left child
	BinTree(this->root->lft).printHelper(o,depth+1,'\\');
	return o;
}

/**
 * Output operator for bintree; calls printHelper
 * @param o Output stream to attach to
 * @param bt Binary tree to print
 * @return New output stream
 */
template <typename K, typename D>
std::ostream& operator<<(std::ostream& o, BinTree<K,D>& bt)
{	
	return bt.printHelper(o, 0, '-');
}
