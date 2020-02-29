#include <iostream>
#include <stdexcept>

template <typename K, typename D>
class BinTree
{
	private:
		struct Node;
		Node* root;
		BinTree(Node* root);
		Node* clsNode(Node* root, const K key);
		Node* sucNode(Node* ret);
		bool recursive;
	public:
		BinTree();
		~BinTree();
		int size();
		int depth();
		int depth(const K key);
		bool ins(const K key, const D& data);
		D del(const K key);
		D& operator[](const K key);
		D& get(const K key);
		K suc(const K key);
		K max();
		K min();
			
	template <typename KK, typename DD>
	friend std::ostream& operator<< (std::ostream&, const BinTree<KK,DD>&);
};

#include "bintree.cpp"
