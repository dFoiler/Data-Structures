#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error

template <typename K, typename D>
class BinTree
{
	private:
		struct Node;
		Node* root;
		BinTree(Node* root);
		Node* clsNode(Node* root, const K key);
		Node* sucNode(Node* node);
		bool recursive;
		std::ostream& printHelper(std::ostream& o, int depth, char child);
	public:
		BinTree();
		~BinTree();
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
	friend std::ostream& operator<< (std::ostream&, BinTree<KK,DD>&);
};

#include "bintree.cpp"
