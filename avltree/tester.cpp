#include <iostream>
#include "avltree.h"

int main()
{
	AVLTree<int,float> bintree;
	int initToAdd = 53;
	int toAdd = initToAdd;
	int mult = 37; //69;
	int terms = 20;
	int mod = 100;
	for(int i = 0; i < terms; ++i)
	{
		std::cout << "Inserting [" << toAdd << "] : " << bintree.ins(toAdd,1) << std::endl;
		if(i == terms-1)
		{
			std::cout << "Depth : " << bintree.depth(toAdd) << std::endl;
			std::cout << "Depth : " << bintree.depth() << std::endl;
			std::cout << "Contains : " << bintree.contains(toAdd) << std::endl;
		}
		std::cout << "Tree : " << bintree << std::endl << std::endl;
		toAdd = (toAdd * mult) % mod;
	}
	toAdd = initToAdd;
	for(int i = 0; i < terms; ++i)
	{
		std::cout << "Changing to " << toAdd << "[" << toAdd << "] : "
			<< (bintree[toAdd]=toAdd) << std::endl;
		toAdd = (toAdd * mult) % mod;
	}
	std::cout << "Tree : " << bintree << std::endl;
	std::cout << "Successor of 53 : " << bintree.suc(initToAdd) << std::endl;
	std::cout << "Full range : [" << bintree.min() << ',' << bintree.max() << ']' << std::endl;
	float* arr = bintree.toArray();
	std::cout << "Array : [" << arr[0];
	for(int i = 1; i < bintree.size(); ++i)
		std::cout << ", " << arr[i];
	std::cout << ']' << std::endl;
	toAdd = initToAdd;
	for(int i = 0; i < terms+1; ++i)
	{
		std::cout << '\n' << std::endl;
		std::cout << "Deleting [" << toAdd << "] : " << bintree.del(toAdd) << std::endl;
		std::cout << "Size : " << bintree.size() << std::endl;
		std::cout << bintree << std::endl;
		std::cout << "Contains : " << bintree.contains(toAdd) << std::endl;
		toAdd = (toAdd * mult*mult*mult) % mod;
	}
}
