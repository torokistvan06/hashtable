#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "list.h"

template<typename T>
class hashtable
{
private:
	int size, lists;
	float stored, load;
	float maxload = 0.75;
	int hash(const T);
	void resize();
	void swap(hashtable& tmp);
public:
	list<T>* table;

	// Konstruktorok,destruktor
	hashtable();
	hashtable(int);
	~hashtable();

	// Adatformáló függvények
	int insert(const T);
	int remove(const T);
	int removeList(const int);
	void removeContent();
	void resize(const int);

	// Kereső függvények
	int findInTable(const T);
	int findInList(const T);
	int findInSpecifiedList(const T,int);

	// Getter függvények.
	int getSize() { return size; };
	int getLists() { return lists; };
	float getStored() { return stored; };
	float getLoad() { return load; };
	float getMaxLoad() { return maxload; };

	// Setter függvény maxload-ra
	void setMaxLoad(float maxload) { this->maxload = maxload; };

	// Kiiró függvény.
	void print();
	void print(FILE*);
};

// A kulcsot adja meg
template<typename T>
int hashtable<T>::hash(const T data)
{
	return (int)data % size;
}

// Alapértelmezett konstruktor, 16-os méretre.
template<typename T>
hashtable<T>::hashtable()
{
	size = 16;
	lists = 0;
	stored = 0;
	load = 0;
	table = new list<T>[size];
}

// Konstruktor adott méretre.
template<typename T>
hashtable<T>::hashtable(int size)
{
	this->size = size;
	lists = 0;
	stored = 0;
	load = 0;
	table = new list<T>[size];
}


// Destruktor.
template<typename T>
hashtable<T>::~hashtable()
{
	delete[] table;
}

// Privát: segéd resize inserthez.
template<typename T>
void hashtable<T>::resize()
{
	hashtable<T> tmp(this->size * 2);
	node<T>* node;
	for (int i = 0; i < this->size; i++)
	{
		node = table[i].head;
		while (node != nullptr)
		{
			tmp.insert(node->data);
			node = node->next;
		}
	}
	swap(tmp);
}

// Újraméretezi a táblát a paraméter szerint.
template<typename T>
void hashtable<T>::resize(const int newSize)
{
	hashtable<T> tmp(newSize);
	tmp.setMaxLoad(this->maxload);
	node<T>* node;
	for (int i = 0; i < this->size; i++)
	{
		node = table[i].head;
		while (node != nullptr)
		{
			tmp.insert(node->data);
			node = node->next;
		}
	}
	swap(tmp);
}

// Segéd függvény a resizeokhoz.
template<typename T>
void hashtable<T>::swap(hashtable<T>& tmp)
{
	std::swap(this->table, tmp.table);
	std::swap(this->size, tmp.size);
	std::swap(this->lists, tmp.lists);
	std::swap(this->stored, tmp.stored);
	std::swap(this->load, tmp.load);
}

// Hozzáad függvény.
template<typename T>
int hashtable<T>::insert(const T data)
{
	if (findInTable(data) == -1)
	{
		int key = hash(data);
		if (table[key].isEmpty())
			lists++;
		table[key].push(data);
		stored++;
		load = stored / size;
		if (load >= maxload)
			resize();
		return 1;
	}
	return 0;
}

// Kivesz függvény.
template<typename T>
int hashtable<T>::remove(const T data)
{
	int key = hash(data);
	
	if (table[key].findByValue(data) != -1)
	{
		table[key].eraseByValue(data);
		if (table[key].isEmpty())
			lists--;
		stored--;
		load = stored / size;
		return 1;
	}
	return 0;
}

// Listatörlő függvény 
template<typename T>
int hashtable<T>::removeList(const int index)
{
	if (index < 0 || index > size)
		return 0;
	stored -= table[index].getSize();
	load = stored / size;
	if (!table[index].isEmpty())
		lists--;
	table[index].clear();
	return 1;
}

// Táblatörlő függvény
template<typename T>
void hashtable<T>::removeContent()
{
	for (int i = 0; i < size; i++)
		removeList(i);
}

// Megkeresi a táblában adott adat kulcsát.
template<typename T>
int hashtable<T>::findInTable(const T data)
{
	int key = hash(data);
	int inTable = table[key].findByValue(data);
	if (inTable != -1)
		return key;
	else
		return -1;
}

// Megkeresi az adott adat kulcsát majd annak a helyét a listában.
template<typename T>
int hashtable<T>::findInList(const T data)
{
	int key = hash(data);
	return table[key].findByValue(data);
}

// Megkeresi adott adat helyét adott listában
template<typename T>
int hashtable<T>::findInSpecifiedList(const T data, int list)
{
	return table[list].findByValue(data);
}

// Kiirja a táblát.
template<typename T>
void hashtable<T>::print()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << i << " : " << table[i] << "\n";
	}
}

// Kiirja a táblát file-ba.
template<typename T>
void hashtable<T>::print(FILE* fout)
{
	for (int i = 0; i < size; i++)
	{
		fprintf(fout,"%d : ", i);
		node<T> tmp = table.head;
		while (tmp != nullptr)
		{
			fprintf(fout, "%d ", tmp->data);
			tmp = tmp->next;
		}
		fprintf(fout, "\n");
	}
}


#endif