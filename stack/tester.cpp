#include <iostream>
#include "stack.h"

int main()
{
	Stack<int> s;
	for(int i = 0; i < 10; ++i)
	{
		s.push(i);
		std::cout << "Current: " << s << std::endl;
	}
	for(int i = 0; i < 5; ++i)
	{
		std::cout << "Pop: " << s.pop() << std::endl;
		std::cout << "Current: " << s << std::endl;
	}
	for(int i = 0; i < 10; ++i)
	{
		s.push(-i);
		std::cout << "Current: " << s << std::endl;
	}
	for(int i = 0; i < 21; ++i)
	{
		std::cout << "Pop: " << s.pop() << std::endl;
		std::cout << "Current: " << s << std::endl;
	}
}
