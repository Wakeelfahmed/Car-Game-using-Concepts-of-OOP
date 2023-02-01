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
	void insert_specfic_Position(int Position, T newvalue) {
		int position_count = 1;
		if (Position > Number_of_Nodes()) {
			cout << "List has less nodes than the place, Node CAN't be inserted!!\n";
			return;
		}
		Node<T>* NewNode = new Node(newvalue);		//NewNode->Data = newvalue;
		Node<T>* p = head;
		while (p != head)
		{
			if (Position == 1) {
				insert_beg(newvalue);
				return;
			}
			else if (Position == Number_of_Nodes()) {
				insert_end(newvalue);
				return;
			}
			else if (position_count == Position - 1 && Position != 0) {
				NewNode->next = p->next;
				p->next = NewNode;
				return;
			}
			p = p->next;		//move to next node
			position_count++;
		}
	}
	void insert_after(T oldvalue, T newvalue) {
		Node<T>* p = head;
		if (isEmpty())
			return;
		do
		{
			if (p->get_Data().X == oldvalue.X && p->get_Data().Y == oldvalue.Y)
			{
				Node<T>* NewNode = new Node(newvalue);
				NewNode->next = p->next;
				p->next = NewNode;
				return;
			}
			p = p->next;
		} while (p != head);
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
	int Search_in_List(T Value_to_search, list& list) {
		Node<T>* p = list.get_head();
		int Position_counter = 1;
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
	list<T> concatenate(const list<T>& list2) {
		list Result = *this;
		Node<T>* p = get_head();	Node<T>* loop2 = list2.get_head();
		while (p->next != get_head())
			p = p->next;
		while (loop2->next != list2.get_head())
			loop2 = loop2->next;
		loop2->next = head;	//connect last node of list2 to head of list1 making circular
		p->next = list2.get_head();//connect last node of list1 to head of list2.
		cout << "Concatenated list is:\n";
		Result.Display_list();
		return Result;
	}
	int Number_of_Nodes() const {
		if (isEmpty())
		{
			//cout << "list is empty!! \n there are no nodes." << endl;
			return 0;
		}
		int Counter = 0;
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
	list(list& list) {
		head = list.head;
	}
	Node<T>* get_Node_by_Pos(int index) {
		int i = 1;
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