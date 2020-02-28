#include <iostream>
#include "bintree.h"

int main()
{
	BinTree<int,int> bintree;
	std::cout << "[BEGIN]" << std::endl;
	std::cout << "Inserting 1-1 : " << bintree.insert(1,1) << std::endl;
	std::cout << "Inserting 2-1 : " << bintree.insert(2,1) << std::endl;
	std::cout << "Inserting 1-3 : " << bintree.insert(1,3) << std::endl;
	std::cout << "Inserting 0-1 : " << bintree.insert(0,1) << std::endl;
	std::cout << "Tree: " << bintree << std::endl;
	std::cout << "Tree: " << bintree << std::endl;
	std::cout << "Changing to 1-5 : " << (bintree.get(1)=5) << std::endl;
	std::cout << "Tree: " << bintree << std::endl;
	std::cout << "Tree: " << bintree << std::endl;
}
