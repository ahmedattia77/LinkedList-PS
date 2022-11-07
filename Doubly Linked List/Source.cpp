#include <iostream>
#include <stack>
#include <string>
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

class double_linked {

	node* head{};
	node* tail{};
	int length = 0;

public:
	void print_length()
	{
		cout << "length : " << length << endl << endl;
	}
	void add_node()
	{
		length++;
	}
	void delete_node()
	{
		length--;
	}
	void link(node* first, node* second)
	{
		// normal insertingthe new data by make tial point to the new item ;
		if (first){ first->next = second; }
		// the addtion part in doublt linkedlist ;
		// its about making the new item point to the prevuos by prev pointer in it ;
		if (second){ second->prev = first; }
			
	}
	void print()
	{
		if (!head) { cout << "empty :\n"; }
		for (node* temp = head; temp; temp = temp->next)
		{
			cout << temp->data << " ";
		}cout << "\n\n";

	//	cout << "head : " << head->data << endl;
	//	cout << "head : " << tail->data << endl;

	}
	void print_reversely()
	{
		if (!tail) { cout << "empty :\n"; }
		for (node* cur = tail; cur; cur = cur->prev)
		{
			cout << cur->data << " ";
		}
	}
	//insertion
	void insert_end(int val)
	{
		add_node(); // 1 2
		node* new_item = new node(val);
		if (!head)
		{
			head = tail = new_item;
		}
		else {
			link(tail , new_item);
			tail = new_item;
		}
	}
	void insert_front(int val)
	{
		add_node();
		node* new_item = new node(val);
		if (!head)
		{
			insert_end(val);
		}	   //     
		else { // 1 2 3 
			link(new_item, head);
			head = new_item;
		}
	}
	void mid_insert(int val)
	{
		node* cur = head;
		node* new_item = new node(val);
		while (cur) { // 1 2 3 5 6
			if (cur->data < val && cur->next->data > val)
			{
				new_item->next = cur->next;
				cur->next->prev = new_item;
				cur->next = new_item;
				new_item->prev = cur;
				break;
			}
				cur = cur->next;
		}
	}
	void sorted_insert(int val)
	{
		
		if (!head) { insert_end(val); add_node(); return; } // 1 2 3 4 
		if (head->data <= val) { insert_end(val); add_node(); return; }
		if (tail->data >= val) { insert_front(val); add_node(); return; }
		
			node* fi = head, * la = tail;
			for (; fi, la; fi = fi->next, la = la->prev)
			{
				if (fi->data <= val && fi->next->data >= val)
				{
					node* item = new node(val); // 1 2 3 4
					fi->next->prev = item;
					item->next = fi->next;
					item->prev = fi;
					fi->next = item;
					add_node();
					return;
				}
				else if (la->data >= val && la->prev->data < val)
				{
					node* item = new node(val);
					//		  l
					// 1 2 3  5
					item->prev = la->prev;
					item->next = la;
					item->prev->next = item;
					la->prev = item;
					add_node();
					return;
				}	
		}
	}
	//deletion
	void delete_front() {
		if (!head)
			return; // 1
		else if (!head->next)
		{
			node* temp = head;
			head = tail = nullptr;
			delete temp;
		}
		else if (!head->next->next) // 1 2 
		{
			node* temp = head->next;
			delete head;
			head = temp;
			head->prev = nullptr;
		}
		else { // 1 2 3
			node* cur = head->next;
			delete(head);
			head = cur;
			head->prev = nullptr;
		}
	
		delete_node();
	}
	void delete_end() 
	{ // O(1) constant time
		if (!head) { return; }

		else if (!head->next)//1
		{
			node* temp = tail;
			head = tail = nullptr;
			delete temp;
			
		}
		else if (!head->next->next)// 1 2
		{
			node* temp = tail->prev;
			delete tail;
			tail = temp;
			tail->next = nullptr;
		}
		else { // 1 2 3 
			node* temp = tail->prev;
			delete tail;
			tail = temp;
			tail->next = nullptr;
		}


			delete_node();
	}
	void delete_link(node* prev , node* cur)
	{
		prev->next = cur->next;
		cur->prev = prev; //prev node for cur
		cur->next->prev = prev; //next node for cur
		delete (cur);
	}
	node* delete_link_from_head(node *cur)
	{	//   c
		// 1 2 3 4 5	
		 // 1 2 3
		if (!cur->prev) {
			node* ret = cur->next;
			delete_front(); 
			return ret;
		}
		else {
			node* ret = cur->prev;
			link(ret, cur->next);
			delete (cur);
			return ret;
		}
		
		delete_node();
	}
	node* delete_link_from_tail(node* last)
	{
		// 1 2 3
		
			node* ret = last->next;
			link(last->prev, last->next);
			delete (last);
			return ret;
		delete_node();
	}
	void delete_with_kay(int val) 
	{ // 1 2 3
		// age cases
		if (val == head->data || !head->next) { delete_front(); delete_node(); return; }
		if (val == tail->data) { delete_end(); delete_node(); return; }
		//main
		node* first = head->next, * last = tail->prev;
		for (; first , last; first = first->next ,last =last->prev) 
		{
			if (first->data == val )
			{
				delete_link(first->prev, first);
				return;
			}						   	//     p l n
			else if (last->data == val) // 1 2 3 4 5 
			{
				last->prev->next = last->next;
				last->next->prev = last->prev;
				delete(last);
				return;
			}
		}
	}
	void test()
	{
		// 1 2 3 4 
		node *temp = head;
		delete_front();
	}
	// start home work ///
	bool check_touch(node* fi, node* las)
	{
		//     h   t
		// 1 2 3 5 4 5 6
		
		if (fi->next == las->prev) { return true; }
		else if (fi->next == las && las->prev == fi) { return true; }
		else {
			return false;
		}
	}
	void del_head_tail(int val)
	{
		if (head->data == val) { delete_front(); }
		if (tail->data == val) { delete_end(); }
	}
	//////////////////////// age cases ;
	void delete_all_nodes_with_key(int val) {
		// age cases
		if (!head) { return; }
		// main

		for (node* cur = head->next; cur;)
		{
			if (cur->data == val)
			{
				if (!cur->next) { return; }
				cur = delete_link_from_head(cur);
			}
			else {
				cur = cur->next;
			}
		}
	}
	void delete_even_positions() {
		if (!head) { return; } // 1 2 3 4
		node* even = head->next;
		for (; even; even = even->next->next)
		{
			even = delete_link_from_head(even);
			if (!even->next){ return; }
				
		}
	}
	void delete_odd_positions(){
		if (!head) { return; } // 1 2 3 4
		node* odd = head->next->next;
		for (; odd; odd = odd->next->next)
		{
			odd = delete_link_from_head(odd); //ret 2
			if (!odd->next) { break; }
		}
		delete_front();
	}
	void delete_odd()
	{
		insert_front(-1); // -1 1 2 3 4
		delete_even_positions();
		delete_front();
	}
	bool is_palindrome(){
	
		node* fi = head, * las = tail;// 1 2 3 2 1
		for (; fi, las; fi = fi->next, las = las->prev)
		{
			if (fi->data != las->data) { return false; }
			if (check_touch(fi, las)) { break; }
		}

		return true;
	}
	///////// home work part 2 DLL medium to hard
	int find_med() {
		if (!head) { return 0; }

		node* first = head, * last = tail;
		for (; first, last; first = first->next, last = last->prev)
		{
			if (last->prev == first->next) // 1 2 3 4
				return last->prev->data;
			else if (last->prev == first)
				return last->data;
		}
	}
	// Tricky
	void find_med2(){
		int coun = 0;
		node* tempH = head, * tempT= tail;
		node* temp = tail;
		while (tempH)
		{
			head = head->next;
			tempH = tempH->next;
			tempT = tempT->prev;
			link(tempT->next,tempH->prev);
			tail = tail->next;
			tempT = tail;
			coun++;
			if (tempH == temp)
			{
				head = head->next;
				tail = tail->next;
				head->prev = nullptr;
				tail->next = nullptr;
				tempH = head;
				break;
			}
		}
		coun = (coun / 2);
		while (coun)
		{
			tempH = tempH->next;
			coun--;
		}
		cout << tempH->data << " " << endl;
	} 
	void find_med3()
	{
		node* slow = head, *fast = head;
		while (fast)
		{
			if (!fast->next) { break; }
			fast = fast->next->next;
			slow = slow->next;

		}
		cout << slow->data << endl;
	}
	void swap_forward_backward(int k)
	{
		if (!head) { return; }
		// age case
		
			// 1 2 3 4
			node* tempH = head, * tempT = tail;
		if (k == 1) {
			head = head->next;
			head->prev = nullptr;
			tempH->next = nullptr;
			tempT->next = tempH;
			tempH->prev = tail;
			tail = tempH;
		}
		else {
		
			while (head->next)
			{
				tempH = tempH->next;
				tempT = tempT->prev;
				if (tempH->next == tempT)
				{
					link(tempH->prev, tempT->next);
					return;
				}
				else if (tempH->next == tempT->prev)
				{
					break;
				}
			}

			link(tempT->prev, tempT->next);
			link(tempH->prev, tempH->next);
			// key 2
			//   h   t
			// 1 2 3 4 5
			//   h t
			// 1 2 3 4

			
		}
	}
	void revers_linked() {
		if (!head) { return; }
		if (!head->next) { return; }
		int l = length;
		node* temp1 = head->next;
		node* temp2 = head;
		while (l != 1) //   h
		{ // 1 2 3 4 5 // 2 1 3 4 5 
			if (!temp1->next)
			{
				tail = tail->prev;
				tail->next = nullptr;
				link(temp1, head);
				head = head->prev;
				head->prev = nullptr;
				break;
			}
			link(temp2, temp1->next);
			link(temp1, head);
			head = head->prev;
			head->prev = nullptr;
			temp1 = temp2->next;
			l--;
		}
	} // solved
	void print_linked(node* temp)
	{
		while (temp)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}cout << endl;
	}
	// handel exception later
	void merg_linked(double_linked& lin2){
		node* temp = head, *temp2 = lin2.head;
		node* ptr = nullptr;
		// age cases					//  lin     lin2
		if (!temp && !temp2) { return; } // empty | empty 
		if (temp && !temp2) { print_linked(temp); return; } // 1 2 | empty
		if (!temp && temp2) { print_linked(temp2); return; }// empty | 1 2 
		// main concept
		while (temp->next && temp2->next)
		{
			
			// 1 4 7 | 2 5 8 
			if (temp->data < temp2->data)
			{
				lin2.head = lin2.head->next;
				lin2.head->prev = nullptr;
				link(temp2, temp->next);
				link(temp, temp2);
				temp2 = lin2.head;
				temp = temp->next->next;
				if (!temp2->next) {
					lin2.head = lin2.tail = nullptr;
					link(temp, temp2);
				}
			}
			else {
				temp = temp->next;
			}
		

		}
	}
	// finshing
};



int main()
{
	cout << "the end of DLL :) \n\n";
	return 0;
}
