#include <iostream>
using namespace std;
struct node {
	int data{};
	node* next{};
	node* prev{};
	node(int data) : data(data) {}

	void set(node* next, node* prev)
	{
		this->next = next;
		this->prev = prev;
	}
};

int main()
{
	cout << "hello world \n";
}