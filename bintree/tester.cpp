#include <iostream>
#include "bintree.h"

int main()
{
	BinTree<int,int> bintree;
	std::cout << "[BEGIN]" << std::endl;
	std::cout << "Inserting 1[1] : " << bintree.ins(1,1) << std::endl;
	std::cout << "Inserting 1[3] : " << bintree.ins(3,1) << std::endl;
	std::cout << "Inserting 3[1] : " << bintree.ins(1,3) << std::endl;
	std::cout << "Inserting 1[0] : " << bintree.ins(0,1) << std::endl;
	std::cout << "Inserting 0[2] : " << bintree.ins(2,0) << std::endl;
	std::cout << "Tree: " << bintree << std::endl;
	std::cout << "Tree: " << bintree << std::endl;
	std::cout << "Changing to 4[2] : " << (bintree[2]=4) << std::endl;
	std::cout << "Tree: " << bintree << std::endl;
	std::cout << "Tree: " << bintree << std::endl;
	std::cout << "Successor of 1 : " << bintree.suc(1) << std::endl;
	std::cout << "Successor of 0 : " << bintree.suc(0) << std::endl;
}
