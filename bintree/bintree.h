#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error

template <typename K, typename D>
class BinTree
{
	private:
		struct Node;
		Node* root;
		BinTree(Node* root);
		Node* clsNode(Node* root, const K& key) const;
		Node* sucNode(Node* node) const;
		bool recursive;
		std::ostream& printHelper(std::ostream& o, int depth, char* path, char child) const;
	public:
		BinTree();
		~BinTree();
		int size() const;
		int depth() const;
		int depth(const K& key) const;
		bool ins(const K& key, const D& data);
		D del(const K& key);
		bool contains(const K& key) const;
		D& operator[](const K& key) const;
		inline D& get(const K& key) const;
		inline void set(const K& key, const D& data);
		K suc(const K& key) const;
		K max() const;
		K min() const;
		D* toArray() const;
			
	template <typename KK, typename DD>
	friend std::ostream& operator<< (std::ostream&, const BinTree<KK,DD>&);
};

#include "bintree.cpp"
