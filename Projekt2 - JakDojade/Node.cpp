#include "node.h"

template<typename T, size_t B_SIZE>
size_t Node<T, B_SIZE>::findLastFilledIndex()
{
	for (int i = B_SIZE - 1; i >= 0; i--)
		if (filled[i] == true)
			return i;
	return -1;
}

template<typename T, size_t B_SIZE>
T& Node<T, B_SIZE>::getLast()
{
	return items[findLastFilledIndex()];
}


template<typename T, size_t B_SIZE>
void Node<T, B_SIZE>::add(const T& item)
{
	if (size < B_SIZE && findLastFilledIndex() != B_SIZE - 1)
	{
		items[findLastFilledIndex() + 1] = item;
		filled[findLastFilledIndex() + 1] = true;
		size++;
	}
	else
		throw "items are full!";
}
template<typename T, size_t B_SIZE>
T& Node<T, B_SIZE>::operator[](size_t index)
{
	if (index >= B_SIZE || index > size)
		throw "out of bounds!";
	size_t i = findMappedIndex(index);
	if (i == -1)
		throw "out of bounds!";
	return items[i];
}

template<typename T, size_t B_SIZE>
size_t Node<T, B_SIZE>::findMappedIndex(size_t index)
{
	for (int i = 0, j = -1; i < B_SIZE; i++)
	{
		if (filled[i] == true)
			j++;
		if (j == index && filled[i] == true)
			return i;
	}
	return -1;
}

template<typename T, size_t B_SIZE>
void Node<T, B_SIZE>::pop()
{
	size--;
	items[findLastFilledIndex()] = T{};
	filled[findLastFilledIndex()] = false;
}
//TODO: pop for index
template<typename T, size_t B_SIZE>
Node<T, B_SIZE>::Node()
{
	for (int i = 0; i < B_SIZE; i++)
		filled[i] = false;
}