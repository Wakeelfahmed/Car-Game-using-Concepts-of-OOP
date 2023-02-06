#pragma once
#include<Windows.h>
template <class T>
class Node
{
public:
	T Data{};
	Node<T>* next;
	Node() : next(0) {}
	Node(T Data) : Data(Data), next(0) {}
	void set_Data(T Data) { this->Data = Data; }
	bool operator==(const Node<T>& other) const {
		return Data == other.Data;
	}

	bool operator==(const T& value) const {
		return Data == value;
	}
	/*bool operator==(Node<T>* Node2) {
		if (Node2->Data == Data && next == Node2->next)
			return 1;
		return 0;
	}
	bool operator==(T Data2) {
		if (Data == Data2)
			return 1;
		return 0;
	}*/
	//T get_Data() const { return Data; }
	T get_Data() { return Data; }
};