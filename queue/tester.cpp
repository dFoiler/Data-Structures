#include <iostream>
#include "queue.h"

int main()
{
	Queue<int> q;
	for(int i = 0; i < 10; ++i)
	{
		q.enqueue(i);
		std::cout << "Current: " << q << std::endl;
	}
	for(int i = 0; i < 5; ++i)
	{
		std::cout << "Dequeue: " << q.dequeue() << std::endl;
		std::cout << "Current: " << q << std::endl;
	}
	for(int i = 0; i < 10; ++i)
	{
		q.push(10-i);
		std::cout << "Current: " << q << std::endl;
	}
	std::cout << "Setting top to 123" << std::endl;
	q.top() = 123;
	std::cout << "Current: " << q << std::endl;
	for(int i = 0; i < 20; ++i)
	{
		std::cout << "Dequeue: " << q.pop() << std::endl;
		std::cout << "Current: " << q << std::endl;
	}
}
