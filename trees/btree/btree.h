#ifndef BTREE_H
#define BTREE_H

#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error

template <typename K, typename D>
class BTree
{
	private:
		struct Node;
		Node* root;
		int m;
		BTree(Node* root, const int m);
		int index(Node* nd, const K& key) const;
		Node* clsNode(const K& key) const;
		void insAt(const K& key, const D& data, Node*, Node*);
		bool recursive;
		std::ostream& printHelper(std::ostream& o, Node* root, const int depth) const;
	public:
		BTree(const int m);
		~BTree();
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
	friend std::ostream& operator<<(std::ostream& o, const BTree<KK,DD>& bt);
};

#include "btree.cpp"

#endif // BTREE_H
