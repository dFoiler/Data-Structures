#include <iostream>
#include "btree.h"
#include "btree.h"

int main()
{
	BTree<int,char> bt(3);
	std::cout << bt << std::endl;
	for(int i = 1; i < 10; ++i)
	{
		std::cout << "bt.ins(" << i << ",' ') : " << bt.ins(i,' ') << std::endl;
		std::cout << bt << std::endl;
	}
}
