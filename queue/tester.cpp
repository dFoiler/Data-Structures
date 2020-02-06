#include <iostream>
#include "queue.cpp"

int main()
{
	Queue<int> q;
	q.enqueue(0);
	std::cout << "Current: " << q << std::endl;
	std::cout << "Top: " << q.top() << std::endl;
	q.enqueue(1);
	std::cout << "Current: " << q << std::endl;
	q.enqueue(1000);
	std::cout << "Current: " << q << std::endl;
	q.enqueue(-5);
	std::cout << "Current: " << q << std::endl;
	std::cout << "Dequeue: " << q.dequeue() << std::endl;
	std::cout << "Current: " << q << std::endl;
	q.enqueue(15);
	for(int i = 0; i < 5; ++i)
	{
		std::cout << "Current: " << q << std::endl;
		std::cout << "Dequeue: " << q.dequeue() << std::endl;
		std::cout << "Current: " << q << std::endl;
	}
}
