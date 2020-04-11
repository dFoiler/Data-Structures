#include <iostream>
#include "linkedlist.h"
#include "linkedlist.h"

int main()
{
	LinkedList<int> list1;
	LinkedList<int> list2;
	for(int i = 0; i < 10; ++i)
	{
		list1.add(i); list2.add(20-i);
		std::cout << "List 1: " << list1 << std::endl;
		std::cout << "List 2: " << list2 << std::endl;
	}
	std::cout << "List 1 += List 2" << std::endl;
	list1 += list2;
	std::cout << list1 << std::endl;
	std::cout << "List 1[list.size()-1] = 23" << std::endl;
	list1[list1.size()-1] = 23;
	std::cout << list1 << std::endl;
	std::cout << "Exchanging 1 and 3" << std::endl;
	list1.exchg(1, 3);
	std::cout << list1 << std::endl;
	std::cout << "Swapping 1 and 3 back" << std::endl;
	list1.swap(1, 3);
	std::cout << list1 << std::endl;
	std::cout << "Sort" << std::endl;
	list1.sort();
	std::cout << list1 << std::endl;
	std::cout << "Reverse" << std::endl;
	list1.reverse();
	std::cout << list1 << std::endl;
	std::cout << "Index of 23 : " << list1.find(23) << std::endl;
	std::cout << "Index of 12 : " << list1.rfind(12) << std::endl;
	std::cout << "Index of -1 : " << list1.find(-1) << std::endl;
	std::cout << "Contains 10 : " << list1.contains(10) << std::endl;
	std::cout << "Contains 11 : " << list1.contains(12) << std::endl;
	std::cout << "List1==List1: " << (list1 == list1) << std::endl;
	std::cout << "List1==List2: " << (list1 == list2) << std::endl;
	for(int i = 19; i >= 0; --i)
	{
		std::cout << "Deleting " << i << " : " << list1.del(i) << std::endl;
		std::cout << list1 << std::endl;
	}
	std::cout << "Accessing list2[100]" << std::endl;
	list2[100];
}
