#include <iostream>
#include <functional>
#include <string>
#include "hashtable.h"

int main()
{
	HashTable<float, std::string> itable(20);
	std::string s = "data string ";
	int terms = 10;
	for(int i = 0; i < terms; ++i)
	{
		std::cout << "Inserting " << s << (char)('A'+i) << " at key " << i << " : ";
		std::cout << itable.ins(i, s+(char)('A'+i)) << std::endl;
	}
	std::cout << "Attempting to insert at key 1 : ";
	std::cout << itable.ins(1, "should fail") << std::endl;
	std::cout << "Current table:" << std::endl << itable;
	s = "new data string ";
	for(int i = 0; i < terms; ++i)
	{
		std::cout << "Changing itable[" << i << "] to " << s << (char)('A'+20-2*i) << " : ";
		std::cout << (itable[i]=s+(char)('A'+20-2*i)) << std::endl;
	}
	std::cout << "Current table:" << std::endl << itable;
	for(int i = 0; i < terms; ++i)
	{
		std::cout << "Setting itable[" << i << "] to " << s << (char)('A'+2*i) << std::endl;
		itable.set(i, s + (char)('A'+2*i));
	}
	std::cout << "Current table:" << std::endl << itable;
	for(int i = -1; i < terms+1; ++i)
	{
		std::cout << "Contains " << i << "? ";
		std::cout << itable.contains(i) << std::endl;
	}
	for(int i = 0; i < terms+1; ++i)
	{
		std::cout << "Deleting key " << i << " : ";
		std::cout << itable.del(i) << std::endl;
	}
}
