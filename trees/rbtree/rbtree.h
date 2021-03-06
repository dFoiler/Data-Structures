#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error

template <typename K, typename D>
class RBTree
{
	private:
		struct Node;
		Node* root;
		RBTree(Node* root);
		Node* clsNode(Node* root, const K& key) const;
		Node* sucNode(Node* node) const;
		Node* sibling(Node* node) const;
		Node* rotLft(Node* root);
		Node* rotRht(Node* root);
		void insRepair(Node* nd);
		void delRepair(Node* toDel, Node* toRep);
		bool recursive;
		std::ostream& printHelper(std::ostream& o, int depth, char* path, char child) const;
	public:
		RBTree();
		~RBTree();
		int size() const;
		int depth() const;
		int depth(const K& key) const;
		int black_depth() const;
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
	friend std::ostream& operator<< (std::ostream&, const RBTree<KK,DD>&);
};

#include "rbtree.cpp"

#endif // RBTREE_H
