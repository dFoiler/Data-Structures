#include <iostream>
#include <stdexcept>

template <typename K, typename D>
class BinTree
{
	private:
		struct Node;
		Node* root;
		BinTree(Node* root);
		bool recursive;
	public:
		BinTree();
		~BinTree();
		bool insert(const K key, const D& data);
		D& operator[](const K key);
		D& get(const K key);
		//bool pop(const K key);
	
	template <typename KK, typename DD>
	friend std::ostream& operator<< (std::ostream&, const BinTree<KK,DD>&);
};

#include "bintree.cpp"
