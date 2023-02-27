#pragma once
#include"Node.h"
template <class T>
class list
{
private:
	Node<T>* head;
public:
	list() : head(NULL) { }
	Node<T>* get_head() const { return head; }
	bool isEmpty() const {
		if (head == NULL)
			return true;
		return false;
	}
	void insert_beg(T v) {
		Node<T>* NewNode = new Node(v);
		if (isEmpty()) {
			head = NewNode;
			NewNode->next = head;
		}
		else {
			NewNode->next = head;
			Node<T>* p = head;
			while (p->next != head)
				p = p->next;
			head = NewNode;
			p->next = head;  //last Node point to head
		}
	}
	void insert_end(T value) {
		Node<T>* NewNode = new Node<T>(value);
		if (isEmpty()) {
			head = NewNode;
			NewNode->next = head;
		}
		else {
			Node<T>* p = head;
			do
			{
				p = p->next;
			} while (p->next != head);
			p->next = NewNode;
			NewNode->next = head;
			return;
		}
	}
	void Display_list() const {
		if (isEmpty())
		{
			cout << "list is empty!!" << endl;
			return;
		}
		Node<T>* p = head;
		cout << "List: \t";
		do
		{
			//cout << p->Data << "\t";
			p = p->next;
		} while (p != head);
		cout << endl;
	}
	short Search_in_List(T Value_to_search, list& list) {
		Node<T>* p = list.get_head();
		short Position_counter = 1;
		do {
			if (p->get_Data() == Value_to_search)
				return Position_counter;
			p = p->next;
			Position_counter++;
		} while (p != list.get_head());
		return 0; // no record found
	}
	void delete_Node(T Value_to_delete) {
		if (isEmpty()) {
			cout << "List is Empty\n"; return;
		}
		else if (!Search_in_List(Value_to_delete, *this)) {
			cout << "Not found in list\n"; return;
		}
		Node<T>* p = head;
		Node<T>* Temp;
		if (Value_to_delete == head->get_Data()) {
			Temp = p;
			if (head->next == head) {
				delete Temp; head = NULL; return;
			}
			else
			{
				do
				{
					p = p->next;
				} while (p->next != head);
				p->next = head->next;
				head = head->next;
				delete Temp;
				return;
			}
		}
		else
		{
			p = head;
			do
			{
				if (p->next->get_Data() == Value_to_delete)
				{
					Temp = p->next;
					p->next = p->next->next;
					delete Temp;
					return;
				}
				p = p->next;
			} while (p->next != head);
			cout << Number_of_Nodes() << endl;
		}
	}
	short Number_of_Nodes() const {
		if (isEmpty())
		{
			//cout << "list is empty!! \n there are no nodes." << endl;
			return 0;
		}
		short Counter = 0;
		Node<T>* p = head;
		do
		{
			Counter++;
			p = p->next;
		} while (p != head);
		return Counter;
	}
	~list() {
		//cout << "Entering ~\n";
		if (isEmpty())
			return;
		Node<T>* p = head;
		Node<T>* q = head->next;
		do {
			//cout << "Deleteing:" << p->Data << endl;
			delete p;
			p = q;
			if (p != head)
				q = q->next;
			if (p == head) {
				//cout << "Returing ~\n";
				//return;
			}
		} while (p != head);
		//cout << "Leaving ~\n";
	}
	Node<T>* get_Node_by_Pos(short index) {
		short i = 1;
		if (head == NULL)
			return NULL;
		Node<T>* p = head;
		do {
			if (i == index)
				return p;
			i++;
			p = p->next;
		} while (p != head);
	}
};