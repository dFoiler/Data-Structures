#include <iostream>
#include "heap.h"
#include "heap.h"

int main()
{
	// Mersenne twister
	int start = 53;
	int mod = 100;
	int mul = (37*37) % 100;
	int terms = 20;
	Heap<float> hp(19);
	int term = start;
	// Insert and then output
	for(int i = 0; i < terms; ++i)
	{
		std::cout << "Inserting " << term << ": " << hp.ins(term/2.0) << std::endl;
		std::cout << hp << std::endl;
		term = (term * mul) % mod;
	}
	std::cout << "Peek: " << hp.peek() << std::endl;
	for(int i = 0; i < terms; ++i)
	{
		std::cout << "Delete: " << hp.del() << std::endl;
		std::cout << hp << std::endl;
	}
}
