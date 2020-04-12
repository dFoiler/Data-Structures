#include <iostream>
#include "trie.h"
#include "trie.h"

int main()
{
	Trie<char,float> t("abcdefghijklmnopqrstuvwxyz", 26);
	std::cout << "Inserting 0 : " << t.ins("", 0,0) << std::endl;
	std::cout << "Inserting e : " << t.ins("e",1,2.81) << std::endl;
	std::cout << "Trie : " << std::endl << t;
	std::cout << "Inserting eg: " << t.ins("ef",2,15) << std::endl;
	std::cout << "Trie : " << std::endl << t;
	return 0;
}
