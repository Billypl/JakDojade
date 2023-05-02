#include "List.h"
#include <iostream>
#include "Node.cpp"

template<typename List>
ListIterator<List>& ListIterator<List>::operator++()

{
	if (ptr != &(nodePtr->getLast()) ||
		(ptr == &(nodePtr->getLast()) && nodePtr->next == nullptr))
	{
		ptr++;
	}
	else
	{
		nodePtr = nodePtr->next;
		ptr = &(*nodePtr)[0];
	}
	return *this;
}

template<typename List>
ListIterator<List> ListIterator<List>::operator++(int)
{
	ListIterator iterator = *this;
	++(*this);
	return iterator;
}

template<typename List>
ListIterator<List>& ListIterator<List>::operator--()
{
	if (ptr == &(*nodePtr)[0])
	{
		nodePtr = nodePtr->prev;
		ptr = &(nodePtr->getLast());
	}
	else
	{
		ptr--;
	}
	return *this;
}

template<typename List>
ListIterator<List> ListIterator<List>::operator--(int)
{
	ListIterator iterator = *this;
	--(*this);
	return iterator;
}

template<typename List>
bool ListIterator<List>::operator==(const ListIterator& other) const
{
	return ptr == other.ptr;
}

template<typename List>
bool ListIterator<List>::operator!=(const ListIterator& other) const
{
	return !((*this) == other);
}

template<typename List>
typename ListIterator<List>::ReferenceType ListIterator<List>::operator*()
{
	return *ptr;
}

template<typename List>
typename ListIterator<List>::PointerType ListIterator<List>::operator->()
{
	return ptr;
}


template<typename T, size_t B_SIZE>
List<T, B_SIZE>::List()
	: first(nullptr), last(nullptr), blocksCount(0) {}

template<typename T, size_t B_SIZE>
List<T, B_SIZE>::List(const List& other)
{
	(*this) = other;
}

template<typename T, size_t B_SIZE>
List<T, B_SIZE>::~List()
{
	erease();
}

template<typename T, size_t B_SIZE>
void List<T, B_SIZE>::add()
{
	T item{};
	add(item);
}

template<typename T, size_t B_SIZE>
void List<T, B_SIZE>::add(const T& item)
{
	if (blocksCount == 0)
	{
		Node<T, B_SIZE>* tmp = new Node<T, B_SIZE>;
		first = tmp;
		last = tmp;
		blocksCount++;
	}

	while (true)
	{
		try {
			last->add(item);
			return;
		}
		catch (...)
		{
			Node<T, B_SIZE>* tmp = new Node<T, B_SIZE>;
			last->next = tmp;
			tmp->prev = last;

			last = tmp;
			blocksCount++;
		}
	}
}

template<typename T, size_t B_SIZE>
T& List<T, B_SIZE>::operator[](size_t index)
{
	return get(index);
}

template<typename T, size_t B_SIZE>
const T& List<T, B_SIZE>::operator[](size_t index) const
{
	return const_cast<List*>(this)->get(index);
}

template<typename T, size_t B_SIZE>
T& List<T, B_SIZE>::get(size_t index)
{
	if (index > getSize() - 1)
		throw "out of bounds!";
	Node<T, B_SIZE>* tmp = first;
	while (index >= 0)
	{
		if (tmp->findMappedIndex(index) == -1 && tmp->next != nullptr)
		{
			index -= tmp->size;
			tmp = tmp->next;
		}
		else
			return (*tmp)[index % B_SIZE];
	}
	return (*tmp)[0]; // trash
}

template<typename T, size_t B_SIZE>
T& List<T, B_SIZE>::getLast()
{
	return (*last)[last->size - 1];
}

template<typename T, size_t B_SIZE>
void List<T, B_SIZE>::operator=(const List& other)
{
	erease();
	for (int i = 0; i < other.getSize(); i++)
		add(other[i]);
}

template<typename T, size_t B_SIZE>
typename List<T, B_SIZE>::Iterator List<T, B_SIZE>::begin()
{
	return List<T, B_SIZE>::Iterator(first, &(*first)[0]);
}

template<typename T, size_t B_SIZE>
typename List<T, B_SIZE>::Iterator List<T, B_SIZE>::end()
{
	return List<T, B_SIZE>::Iterator(last, &(last->getLast()) + 1);
}

template<typename T, size_t B_SIZE>
void List<T, B_SIZE>::pop()
{
	if (blocksCount == 0 || first->size == 0)
		throw "list is empty!";
	deleteEmptyNode(last);
	last->pop();
}

template<typename T, size_t B_SIZE>
void List<T, B_SIZE>::pop(size_t index)
{
	if (index > getSize() - 1)
		throw "out of bounds!";
	Node<T, B_SIZE>* tmp = first;
	while (index >= 0)
	{
		if (tmp->findMappedIndex(index) == -1 && tmp->next != nullptr)
		{
			index -= tmp->size;
			tmp = tmp->next;
		}
		else
		{
			//TODO: use pop for node index
			(*tmp).items[tmp->findMappedIndex(index % B_SIZE)] = T{};
			(*tmp).filled[tmp->findMappedIndex(index % B_SIZE)] = false;
			tmp->size--;
			deleteEmptyNode(tmp);
			return;
		}
	}
}

template<typename T, size_t B_SIZE>
void List<T, B_SIZE>::print() const
{
	for (int i = 0; i < getSize(); i++)
		std::cout << (*this)[i] << " ";
	std::cout << "\n";
}

template<typename T, size_t B_SIZE>
bool List<T, B_SIZE>::isEmpty() const
{
	return getSize() == 0;
}

template<typename T, size_t B_SIZE>
void List<T, B_SIZE>::erease()
{
	if (blocksCount == 0)
		return;
	else if (blocksCount == 1)
	{
		delete last;
		first = nullptr;
		last = nullptr;
		blocksCount--;
		return;
	}
	Node<T, B_SIZE>* tmp = first->next;
	while (tmp != nullptr)
	{
		delete first;
		first = tmp;
		tmp = tmp->next;
	}
}

template<typename T, size_t B_SIZE>
void List<T, B_SIZE>::deleteEmptyNode(Node<T, B_SIZE>* emptyNode)
{
	if (emptyNode->size == 0)
	{
		if (blocksCount == 1)
		{
			delete emptyNode;
			emptyNode = nullptr;
			first = nullptr;
		}
		else if (emptyNode->next == nullptr) // end of list
		{
			Node<T, B_SIZE>* tmp = emptyNode->prev;
			delete emptyNode;
			tmp->next = nullptr;
			last = tmp;
		}
		else if (emptyNode->prev == nullptr) // start of list
		{
			Node<T, B_SIZE>* tmp = emptyNode->next;
			delete emptyNode;
			tmp->prev = nullptr;
			first = tmp;
		}
		else // in the middle
		{
			Node<T, B_SIZE>* next = emptyNode->next;
			Node<T, B_SIZE>* prev = emptyNode->prev;
			delete emptyNode;
			next->prev = prev;
			prev->next = next;
		}
		blocksCount--;
	}
}

template<typename T, size_t B_SIZE>
size_t List<T, B_SIZE>::getSize() const
{
	Node<T, B_SIZE>* tmp = first;
	size_t size = 0;
	while (tmp != nullptr)
	{
		size += tmp->size;
		tmp = tmp->next;
	}
	return size;
}

template<typename T, size_t B_SIZE>
std::ostream& operator<<(std::ostream& os, const List<T, B_SIZE>& list)
{
	list.print();
	return os;
}
