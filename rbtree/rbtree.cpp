/**
 * Standard red-black search tree node
 * Includes left, right, and parent
 */
template <typename K, typename D>
struct RBTree<K,D>::Node
{
	K key; D data;
	Node *lft, *rht, *par;
	// Use 1 for red and 0 for black
	bool color;
	
	inline Node() : key(0x0), data(0x0), lft(0x0), rht(0x0), par(0x0), color(1) {}
	inline Node(K key, D data, Node* par) : key(key), data(data),
		lft(0x0), rht(0x0), par(par), color(1) {}
};

/**
 * Standard default constructor
 * Sets root to null and makes the object nonrecursive
 */
template <typename K, typename D>
inline RBTree<K,D>::RBTree()
{
	this->root = 0x0;
	this->recursive = false;
}

/**
 * Initializes a tree with given root, declared as recursive
 * @param root The root of this tree
 */
template <typename K, typename D>
inline RBTree<K,D>::RBTree(Node* root)
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
RBTree<K,D>::~RBTree()
{
	// There's nothing here to delete
	if(!this->root || this->recursive) // Don't delete temp objects
		return;
	// Create stack objects that will be recursively deleted automatically
	RBTree rht(this->root->rht); rht.recursive = false;
	RBTree lft(this->root->lft); lft.recursive = false;
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
typename RBTree<K,D>::Node* RBTree<K,D>::clsNode(Node* root, const K& key) const
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
typename RBTree<K,D>::Node* RBTree<K,D>::sucNode(Node* node) const
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
 * Helper method; used to find siblings and uncles
 * @param node Node to find sibling of
 * @return Sibling
 */
template <typename K, typename D>
typename RBTree<K,D>::Node* RBTree<K,D>::sibling(Node* node) const
{
	// Root has no sibling
	if(!node->par)
		return 0x0;
	// We are the left child
	if(node == node->par->lft)
		return node->par->rht;
	// We are the right child
	return node->par->lft;
}

/**
 * Rebalance helper; rotates the given node left
 * @param root Node to rotate as root
 * @return The node replacing root
 */
template <typename K, typename D>
typename RBTree<K,D>::Node* RBTree<K,D>::rotLft(Node* root)
{
	Node* child = root->rht;
	// Promote child
	if(root->par)
	{
		if(root == root->par->lft)
			root->par->lft = child;
		else
			root->par->rht = child;
	}
	else
		this->root = child;
	child->par = root->par;
	root->par = child;
	// Reorder the children
	root->rht = child->lft;
	if(root->rht)
		root->rht->par = root;
	child->lft = root;
	// Return new root
	return child;
}

/**
 * Rebalance helper; rotates the given node right
 * @param root Node to rotate as root
 * @return The node replacing root
 */
template <typename K, typename D>
typename RBTree<K,D>::Node* RBTree<K,D>::rotRht(Node* root)
{
	Node* child = root->lft;
	// Promote child
	if(root->par)
	{
		if(root == root->par->lft)
			root->par->lft = child;
		else
			root->par->rht = child;
	}
	else
		this->root = child;
	child->par = root->par;
	root->par = child;
	// Reorder the children
	root->lft = child->rht;
	if(root->lft)
		root->lft->par = root;
	child->rht = root;
	// Return new root
	return child;
}

/**
 * Computes and returns the size of the tree recursively
 * @return Number of nodes in the tree
 */
template <typename K, typename D>
int RBTree<K,D>::size() const
{
	// Is there anything there?
	if(!this->root)
		return 0;
	// Recursive call
	return 1 + RBTree<K,D>(this->root->lft).size()
		+ RBTree<K,D>(this->root->rht).size();
}

/**
 * Computes and returns zero-indexed depth of a node
 * Throws an error if the node is not present
 * @param key Key to walk with
 * @return Zero-indexed depth of the key
 */
template <typename K, typename D>
int RBTree<K,D>::depth(const K& key) const
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
int RBTree<K,D>::depth() const
{
	// Empty tree gives -1
	if(!this->root)
		return -1;
	// Run recursive calls
	int dLft = RBTree<K,D>(this->root->lft).depth();
	int dRht = RBTree<K,D>(this->root->rht).depth();
	return 1 + (dLft > dRht ? dLft : dRht);
}

/**
 * Insert helper method
 */
template <typename K, typename D>
void RBTree<K,D>::insRepair(Node* nd)
{
	// We are root
	if(this->root == nd)
	{
		// Root is black
		nd->color = 0;
		return;
	}
	// Parent black
	if(!nd->par->color)
		// Being red breaks no rules
		return;
	// Parent is red
	Node* unc = this->sibling(nd->par);
	// Uncle is red
	if(unc && unc->color)
	{
		// Toggle both parent and uncle
		nd->par->color = unc->color = 0;
		// To fix black paths, grandparent is red
		nd->par->par->color = 1;
		// But now we have to recurse up with red
		return this->insRepair(nd->par->par);
	}
	// Uncle is black---hard case
	// We want par/nd pair to be on top so we can toggle par
	// Left-right or right-left child problems
	if(nd == nd->par->rht && nd->par == nd->par->par->lft)
		nd = this->rotLft(nd->par)->lft;
	else if(nd == nd->par->lft && nd->par == nd->par->par->rht)
		nd = this->rotRht(nd->par)->rht;
	// Rotate par on top
	if(nd == nd->par->lft)
		this->rotRht(nd->par->par);
	else
		this->rotLft(nd->par->par);
	// Toggle colors; old gpar is now nd's sibling
	nd->par->color = 0; this->sibling(nd)->color = 1;
}

/**
 * Inserts into the binary tree
 * @param key Key of the inserted node
 * @param data Data to be stored in the inserted node
 * @return Success
 */
template <typename K, typename D>
bool RBTree<K,D>::ins(const K& key, const D& data)
{
	Node* par = this->clsNode(this->root, key);
	// Was the tree empty?
	if(!par)
	{
		this->root = new Node(key, data, 0x0);
		// Root is black
		this->root->color = 0;
		return true;
	}
	// Now compare with parent
	if(key == par->key)	// Key already in use
		return false;
	else if(key < par->key) // To the left
	{
		par->lft = new Node(key, data, par);
		this->insRepair(par->lft);
	}
	else			// To the right
	{
		par->rht = new Node(key, data, par);
		this->insRepair(par->rht);
	}
	return true;
}

/**
 * Deletes an element by key
 * Throws an error if the key is nonexistant
 * @param key Key of node to delete
 * @return Value stored in removed element
 */
template <typename K, typename D>
D RBTree<K,D>::del(const K& key)
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
inline bool RBTree<K,D>::contains(const K& key) const
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
D& RBTree<K,D>::operator[](const K& key) const
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
inline D& RBTree<K,D>::get(const K& key) const
{
	return (*this)[key];
}

/**
 * Sets data at key to data
 * Basically calls []
 * @param key Key to set
 * @param data Data to set key to
 */
template <typename K, typename D>
inline void RBTree<K,D>::set(const K& key, const D& data)
{
	(*this)[key] = data;
}

/**
 * Returns the successor node
 * Throws an error if node is invalid or if node is max
 * @param key Key to walk with
 * @return Next key in the tree
 */
template <typename K, typename D>
inline K RBTree<K,D>::suc(const K& key) const
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
K RBTree<K,D>::max() const
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
K RBTree<K,D>::min() const
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
D* RBTree<K,D>::toArray() const
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
std::ostream& RBTree<K,D>::printHelper(std::ostream& o, int depth, char* path, char child) const
{
        // Degenerate base case
        if(!this->root) return o;
        // Right child
        path[depth] = '1';  
	RBTree(this->root->rht).printHelper(o, depth+1, path, '/');
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
	// Color red if red
	if(this->root->color)
		o << "\033[91m";
        o << this->root->data << '[' << this->root->key << ']' << "\033[0m" << std::endl;
        // Left child
        path[depth] = '0';
        RBTree(this->root->lft).printHelper(o, depth+1, path, '\\');
        return o;
}

/**
 * Output operator for bintree; calls printHelper
 * @param o Output stream to attach to
 * @param bt Binary tree to print
 * @return New output stream
 */
template <typename K, typename D>
std::ostream& operator<<(std::ostream& o, const RBTree<K,D>& bt)
{
	char path[bt.depth()];
	return bt.printHelper(o, 0, path, '-');
}