#include <iostream>
#include "trie.h"
#include "trie.h"

int main()
{
	Trie<char,float> t("abcdefghijklmnopqrstuvwxyz", 26);
	std::cout << "Inserting 0 : " << t.ins("",0,0) << std::endl;
	std::cout << "Trie : " << std::endl << t;
	std::cout << "Inserting ef: " << t.ins("ef",2,15.81) << std::endl;
	std::cout << "Trie : " << std::endl << t;
	std::cout << "Depth : " << t.depth() << std::endl << std::endl;
	std::cout << "Inserting e : " << t.ins("e",1,2.81) << std::endl;
	std::cout << "Trie : " << std::endl << t;
	std::cout << "Depth : " << t.depth() << std::endl << std::endl;
	std::cout << "Inserting e : " << t.ins("e",1,-1) << std::endl;
	std::cout << "Trie : " << std::endl << t;
	char sample[6] = {'a','b','c','d','e','f'};
	for(int i = 6; i >= 0; --i)
	{
		std::cout << "Inserting " << sample << "[:" << i << ']' << " : " << t.ins("abcdefg",i,i) << std::endl;
		std::cout << "Trie : " << std::endl << t;
		std::cout << "Depth : " << t.depth() << std::endl << std::endl;
	}
	
	std::cout << "t.contains(\"abcdefg\",6) : " << t.contains("abcdefg",6) << std::endl;
	std::cout << "t.contains(\"abcdefg\",7) : " << t.contains("abcdefg",7) << std::endl;
	
	std::cout << "t.get(\"abcd\",4) =  3.1415 : " << (t.get("abcd",4)=3.1415) << std::endl;
	std::cout << "Trie : " << std::endl << t << std::endl;
	std::cout << "t.set(\"\",0,4)" << std::endl;
	t.set("",0,4);
	std::cout << "Trie : " << std::endl << t << std::endl;
	
	for(int i = 4; i < 7; ++i)
	{
		std::cout << "t.del(\"" << sample << "\"," << i << ") : " << t.del(sample,i) << std::endl;
		std::cout << "Trie : " << std::endl << t << std::endl;
	}
	for(int i = 0; i < 4; ++i)
	{
		std::cout << "t.del(\"" << sample << "\"," << i << ") : " << t.del(sample,i) << std::endl;
		std::cout << "Trie : " << std::endl << t << std::endl;
	}
	// Try setting root for the fun of it
	t.set("",0,-1);
	return 0;
}
