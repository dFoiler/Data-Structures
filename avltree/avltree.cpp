/**
 * Standard AVL tree node
 * Includes left, right, and parent
 */
template <typename K, typename D>
struct AVLTree<K,D>::Node
{
	K key; D data;
	Node *lft, *rht, *par;
	long ht;
	
	inline Node() : key(0x0), data(0x0), lft(0x0), rht(0x0), par(0x0), ht(0) {}
	inline Node(K key, D data, Node* par) : key(key), data(data),
		lft(0x0), rht(0x0), par(par), ht(0) {}
};

/**
 * Standard default constructor
 * Sets root to null and makes the object nonrecursive
 */
template <typename K, typename D>
inline AVLTree<K,D>::AVLTree()
{
	this->root = 0x0;
	this->recursive = false;
}

/**
 * Initializes a tree with given root, declared as recursive
 * @param root The root of this tree
 */
template <typename K, typename D>
inline AVLTree<K,D>::AVLTree(Node* root)
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
AVLTree<K,D>::~AVLTree()
{
	// There's nothing here to delete
	if(!this->root || this->recursive) // Don't delete temp objects
		return;
	// Create stack objects that will be recursively deleted automatically
	AVLTree rht(this->root->rht); rht.recursive = false;
	AVLTree lft(this->root->lft); lft.recursive = false;
	// Now delete the current pointer
	delete this->root;
}

/**
 * Returns the node closest to the given key
 * @param root Root to begin the search
 * @param key Key to search through the tree with
 * @return Pointer to node containing the key
 */
template <typename K, typename D>
typename AVLTree<K,D>::Node* AVLTree<K,D>::clsNode(Node* root, const K key)
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
typename AVLTree<K,D>::Node* AVLTree<K,D>::sucNode(Node* node)
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
 * Rebalance helper; rotates the given node left
 * @param root Node to rotate as root
 * @return The node replacing root
 */
template <typename K, typename D>
typename AVLTree<K,D>::Node* AVLTree<K,D>::rotLft(Node* root)
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
	// Update heights
	this->setHt(root); // root is child of child
	this->setHt(child);
	// Return new root
	return child;
}

/**
 * Rebalance helper; rotates the given node right
 * @param root Node to rotate as root
 * @return The node replacing root
 */
template <typename K, typename D>
typename AVLTree<K,D>::Node* AVLTree<K,D>::rotRht(Node* root)
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
	// Update heights
	this->setHt(root); // root is child of child
	this->setHt(child);
	// Return new root
	return child;
}

/**
 * Rebalance helper; sets the height of the node
 * Assumes height of lft and rht are accurate
 * @return Height of the node
 */
template <typename K, typename D>
long AVLTree<K,D>::setHt(Node* nd)
{
	nd->ht = 0;
	// Has a left child
	if(nd->lft)
	{
		// Is the rht larger?
		if(nd->rht && nd->rht->ht > nd->lft->ht)
			nd->ht = nd->rht->ht + 1;
		else
			nd->ht = nd->lft->ht + 1;
	}
	// Has only a right child
	else if (nd->rht)
		nd->ht = nd->rht->ht + 1;
	// Return height
	return nd->ht;
}

/**
 * Rebalances the AVL tree, going up from bot
 * @param bot Node to trace upwards from
 */
template <typename K, typename D>
void AVLTree<K,D>::rebal(Node* bot)
{
	// Work upwards
	while(bot)
	{
		// Set the height correctly before continuing
		this->setHt(bot);
		long lftHt = bot->lft ? bot->lft->ht : -1;
		long rhtHt = bot->rht ? bot->rht->ht : -1;
		// Left-heavy
		if(lftHt - rhtHt > 1)
		{
			// Test if subree is left- or right-heavy
			lftHt = bot->lft->lft ? bot->lft->lft->ht : -1;
			rhtHt = bot->lft->rht ? bot->lft->rht->ht : -1;
			// Left-heavy
			if(lftHt > rhtHt)
				bot = this->rotRht(bot);
			// Right-heavy
			else
			{
				this->rotLft(bot->lft);
				bot = this->rotRht(bot);
			}
		}
		// Right-heavy
		else if(rhtHt - lftHt > 1)
		{
			// Test if subtree is left- or right-heavy
			lftHt = bot->rht->lft ? bot->rht->lft->ht : -1;
			rhtHt = bot->rht->rht ? bot->rht->rht->ht : -1;
			// Left-heavy
			if(lftHt > rhtHt)
			{
				this->rotRht(bot->rht);
				bot = this->rotLft(bot);
			}
			// Right-heavy
			else
				bot = this->rotLft(bot);
		}
		bot = bot->par; // Iterate upwards
	}
}

/**
 * Computes and returns the size of the tree recursively
 * @return Number of nodes in the tree
 */
template <typename K, typename D>
int AVLTree<K,D>::size()
{
	// Is there anything there?
	if(!this->root)
		return 0;
	// Recursive call
	return 1 + AVLTree<K,D>(this->root->lft).size()
		+ AVLTree<K,D>(this->root->rht).size();
}

/**
 * Computes and returns zero-indexed depth of a node
 * Throws an error if the node is not present
 * @param key Key to walk with
 * @return Zero-indexed depth of the key
 */
template <typename K, typename D>
int AVLTree<K,D>::depth(const K key)
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
int AVLTree<K,D>::depth()
{
	// Empty tree gives -1
	if(!this->root)
		return -1;
	// Run recursive calls
	int dLft = AVLTree<K,D>(this->root->lft).depth();
	int dRht = AVLTree<K,D>(this->root->rht).depth();
	return 1 + (dLft > dRht ? dLft : dRht);
}

/**
 * Inserts into the binary tree
 * @param key Key of the inserted node
 * @param data Data to be stored in the inserted node
 * @return Success
 */
template <typename K, typename D>
bool AVLTree<K,D>::ins(const K key, const D& data)
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
	{
		par->lft = new Node(key, data, par);
		this->rebal(par->lft);
	}
	else			// To the right
	{
		par->rht = new Node(key, data, par);
		this->rebal(par->rht);
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
D AVLTree<K,D>::del(const K key)
{
	// Get the node
	Node* toDelete = this->clsNode(this->root, key);
	if(!toDelete || toDelete->key != key)
		throw std::range_error("del received invalid key");
	D r(toDelete->data);
	Node* toReplace = 0x0; // Assume no children
	Node* toRebal = toDelete->par;
	// toDelete has two children
	if(toDelete->lft && toDelete->rht)
	{
		// Replacement is successor; no left children
		toReplace = this->sucNode(toDelete);
		// Assume toReplace->par == toDelete for now
		toRebal = toReplace;
		// These concern rht of toDelete or par of toReplace
		if(toReplace->par != toDelete)
		{
			// Actually rebalance from parent
			toRebal = toReplace->par;
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
		// Rebalance starting here
		toRebal = toReplace;
	}
	// Change toDelete parent relationships
	if(toDelete == this->root)
		this->root = toReplace;
	else if(toDelete == toDelete->par->lft)
		toDelete->par->lft = toReplace;
	else
		toDelete->par->rht = toReplace;
	// Rebalance, delete, and exit
	delete toDelete;
	this->rebal(toRebal);
	return r;
}

/**
 * Checks if the tree contains given key
 * @param key Key to walk with
 * @return True iff key is present in tree
 */
template <typename K, typename D>
inline bool AVLTree<K,D>::contains(const K key)
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
D& AVLTree<K,D>::operator[](const K key)
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
inline D& AVLTree<K,D>::get(const K key)
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
inline K AVLTree<K,D>::suc(const K key)
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
K AVLTree<K,D>::max()
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
K AVLTree<K,D>::min()
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
D* AVLTree<K,D>::toArray()
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
 * Output operator for bintree
 * Uses nested parantheses to denote parent-child relationships
 * @param o Output stream to attach to
 * @param bt Binary tree to print
 */
template <typename K, typename D>
std::ostream& operator<<(std::ostream& o, const AVLTree<K,D>& bt)
{
	// Base case, natuarlly
	if(!bt.root)
		return o;
	// Output data, key, and parent key in order
	o << bt.root->data << '[' << bt.root->key << ',' << bt.root->ht << "]{";
	if(bt.root->par) o << bt.root->par->key;
	o << "} (";
	// Recursive calls to subtrees
	o << AVLTree<K,D>(bt.root->lft) << ") (" << AVLTree<K,D>(bt.root->rht);
	return o << ')';
}
