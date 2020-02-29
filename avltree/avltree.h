#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error

template <typename K, typename D>
class AVLTree
{
	private:
		struct Node;
		Node* root;
		AVLTree(Node* root);
		Node* clsNode(Node* root, const K key);
		Node* sucNode(Node* node);
		bool recursive;
	public:
		AVLTree();
		~AVLTree();
		int size();
		int depth();
		int depth(const K key);
		bool ins(const K key, const D& data);
		D del(const K key);
		bool contains(const K key);
		D& operator[](const K key);
		D& get(const K key);
		K suc(const K key);
		D* toArray();
		K max();
		K min();
			
	template <typename KK, typename DD>
	friend std::ostream& operator<< (std::ostream&, const AVLTree<KK,DD>&);
};

#include "avltree.cpp"
