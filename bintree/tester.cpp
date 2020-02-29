#include <iostream>
#include "bintree.h"

int main()
{
	BinTree<int,char> bintree;
	std::cout << "[BEGIN]" << std::endl;
	int toAdd = 53;
	int terms = 20;
	for(int i = 0; i < terms; ++i)
	{
		std::cout << "Inserting [" << toAdd << "] : " << bintree.ins(toAdd,' ') << std::endl;
		std::cout << "Tree : " << bintree << std::endl;
		toAdd = (toAdd * 37) % 100;
	}
	toAdd = 53;
	for(int i = 0; i < terms; ++i)
	{
		std::cout << "Changing to " << (char)('a'+i) << "[" << toAdd << "] : "
			<< (bintree[toAdd]='a'+i) << std::endl;
		toAdd = (toAdd * 37) % 100;
	}
	std::cout << "Tree : " << bintree << std::endl;
	std::cout << "Successor of 53 : " << bintree.suc(53) << std::endl;
	toAdd = 53;
	for(int i = 0; i < terms; ++i)
	{
		std::cout << '\n' << std::endl;
		std::cout << "Deleting [" << toAdd << "] : " << bintree.del(toAdd) << std::endl;
		std::cout << bintree << std::endl;
		toAdd = (toAdd * 37) % 100;
	}
}
