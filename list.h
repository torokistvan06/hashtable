#ifndef LIST_H
#define LIST_H

#include <iostream>

template<typename T>
class list;

template<typename T>
class node
{
	node* prev;
	T data;
	node* next;
	friend class list<T>;
	template<typename> friend class hashtable;
public:
	node(T data) { prev = nullptr;  this->data = data; next = nullptr; }
	std::ostream& print(std::ostream& out) { return out << data; };
};

template<typename T>
std::ostream& operator<<(std::ostream& out, node<T>* that)
{
	return that->print(out);
}

template<typename T>
class list
{
	node<T>* head;
	node<T>* tail;
	int elements;
public:
	template<typename> friend class hashtable;
	list(); //
	~list(); //

	void clear(); 
	void push(const T); 
	void pop(); 
	int findByValue(const T);  // Returns index of value, -1 if does not contain
	void eraseByValue(const T); 
	int getSize() { return elements; };
	bool isEmpty(); 
	std::ostream& print(std::ostream&); 
};

template<typename T>
list<T>::list()
{
	head = nullptr;
	tail = nullptr;
	elements = 0;
}

template<typename T>
list<T>::~list()
{
	node<T>* tmp = head;
	while (head != nullptr)
	{
		head = head->next;
		delete tmp;
		tmp = head;
	}
}

template<typename T>
void list<T>::clear()
{
	node<T>* tmp = head;
	while (head != nullptr)
	{
		head = head->next;
		delete tmp;
		tmp = head;
	}
	elements = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
void list<T>::push(const T data)
{
	node<T>* tmp = new node<T>(data);
	if (elements == 0)
	{
		tmp->prev = nullptr;
		tmp->next = nullptr;
		head = tail = tmp;
	}
	else
	{
		tmp->next = head;
		head->prev = tmp;
		head = tmp;
	}
	++elements;
}

template<typename T>
void list<T>::pop()
{
	if (elements == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		node<T>* tmp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete tmp;
	}
	--elements;
}

template<typename T>
bool list<T>::isEmpty()
{
	return elements == 0;
}

template<typename T>
std::ostream& list<T>::print(std::ostream& out)
{
	node<T>* curr = head;
	while (curr != nullptr)
	{
		out << curr << " ";
		curr = curr->next;
	}
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, list<T>& that)
{
	return that.print(out);
}

template<typename T>
int list<T>::findByValue(const T data)
{
	node<T>* curr = head;
	int i = 0;
	while (curr != nullptr)
	{
		if (curr->data == data)
			return i;
		i++;
		curr = curr->next;
	}
	return -1;
}

template<typename T>
void list<T>::eraseByValue(const T data)
{
	node<T>* curr = head;
	if (elements == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		elements--;
	}
	else
		while (curr != nullptr)
		{
			if (curr->data == data)
			{
				if (curr == head)
				{
					head = head->next;
					head->prev = nullptr;
					delete curr;
					break;
				}
				else if (curr == tail)
				{
					tail = tail->prev;
					tail->next = nullptr;
					delete curr;
					break;
				}
				else
				{
					curr->next->prev = curr->prev;
					curr->prev->next = curr->next;
					delete curr;
					break;
				}
			}
			curr = curr->next;
		}
}

#endif