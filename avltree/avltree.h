#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error

template <typename K, typename D>
class AVLTree
{
	private:
		struct Node;
		Node* root;
		AVLTree(Node* root);
		Node* clsNode(Node* root, const K key) const;
		Node* sucNode(Node* node) const;
		Node* rotLft(Node* root);
		Node* rotRht(Node* root);
		long setHt(Node* nd);
		void rebal(Node* bot);
		std::ostream& printHelper(std::ostream&, int depth, bool* path, char child) const;
		bool recursive;
	public:
		AVLTree();
		~AVLTree();
		int size() const;
		inline int depth() const;
		int depth(const K key) const;
		bool ins(const K key, const D& data);
		D del(const K key);
		bool contains(const K key) const;
		D& operator[](const K key) const;
		inline D& get(const K key) const;
		K suc(const K key) const;
		K max() const;
		K min() const;
		D* toArray() const;
			
	template <typename KK, typename DD>
	friend std::ostream& operator<< (std::ostream&, const AVLTree<KK,DD>&);
};

#include "avltree.cpp"
