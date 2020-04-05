#include <iostream>	// std::ostream
#include <stdexcept>	// std::range_error
#include <functional>	// std::hash from C++11

template <typename K, typename D>
class HashTable
{
	private:
		int size;
		std::hash<K> hasher;
		struct Entry;
		Entry** table;
	public:
		inline HashTable(int size);
		~HashTable();
		bool ins(const K& key, const D& data);
		D del(const K& key);
		bool contains(const K& key) const;
		D& operator[](const K& key) const;
		inline D& get(const K& key) const;
		inline void set(const K& key, const D& data);
	
	template <typename KK, typename DD>
	friend std::ostream& operator<<(std::ostream& o, const HashTable<KK,DD>& ht);
};

#include "hashtable.cpp"
