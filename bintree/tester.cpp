#include <iostream>
#include "bintree.h"

int main()
{
	BinTree<int,float> bintree;
	int toAdd = 53;
	int terms = 20;
	for(int i = 0; i < terms; ++i)
	{
		std::cout << "Inserting [" << toAdd << "] : " << bintree.ins(toAdd,0) << std::endl;
		std::cout << "Depth : " << bintree.depth(toAdd) << std::endl;
		std::cout << "Tree : " << std::endl << bintree;
		std::cout << "Depth : " << bintree.depth() << std::endl;
		std::cout << "Contains : " << bintree.contains(toAdd) << std::endl << std::endl;
		toAdd = (toAdd * 37) % 100;
	}
	toAdd = 53;
	for(int i = 0; i < terms; ++i)
	{
		std::cout << "Changing to " << toAdd << "[" << toAdd << "] : ";
		if(i % 2 == 0)
			std::cout << (bintree[toAdd]=toAdd) << std::endl;
		else
		{
			bintree.set(toAdd, toAdd);
			std::cout << bintree.get(toAdd) << std::endl;
		}
		toAdd = (toAdd * 37) % 100;
	}
	std::cout << "Tree : " << std::endl << bintree;
	std::cout << "Successor of 53 : " << bintree.suc(53) << std::endl;
	std::cout << "Full range : [" << bintree.min() << ',' << bintree.max() << ']' << std::endl;
	float* arr = bintree.toArray();
	std::cout << "Array : [" << arr[0];
	for(int i = 1; i < bintree.size(); ++i)
		std::cout << ", " << arr[i];
	std::cout << ']' << std::endl;
	toAdd = 53 % 100;
	for(int i = 0; i < terms+1; ++i)
	{
		std::cout << '\n' << std::endl;
		std::cout << "Deleting [" << toAdd << "] : " << bintree.del(toAdd) << std::endl;
		std::cout << "Size : " << bintree.size() << std::endl;
		std::cout << std::endl << bintree;
		std::cout << "Contains : " << bintree.contains(toAdd) << std::endl;
		toAdd = (toAdd * 37*37*37) % 100;
	}
}
