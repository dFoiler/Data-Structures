#ifndef TRIE_H
#define TRIE_H

#include <iostream>	// std::ostream&
#include <stdexcept>	// std::range_error

template <typename K, typename D>
class Trie
{
	private:
		struct Node;
		Node* root;
		Trie(Node* root, const K* lets, const int numLets);
		Node* clsNode(const K* key, const int keyLen) const;
		K* lets;
		int numLets;
		bool recursive;
		int index(const K& let) const;
		std::ostream& printHelper(std::ostream&, Node* root, K*, int) const;
	public:
		Trie(const K* lets, const int numLets);
		~Trie();
		int depth() const;
		bool ins(const K* key, const int keyLen, const D& data);
		D del(const K* key, const int keyLen);
		inline bool contains(const K* key, const int keyLen) const;
		inline D& get(const K* key, const int keyLen) const;
		inline void set(const K* key, const int keyLen, const D& data);
	
	template <typename KK, typename DD>
	friend std::ostream& operator<<(std::ostream& o, const Trie<KK,DD>& t);
};

#include "trie.cpp"

#endif // TRIE_H
