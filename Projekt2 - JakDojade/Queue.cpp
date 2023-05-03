#include "Queue.h"

template<typename T>
T Queue<T>::beginning()
{
	return buffer[0];
}

template<typename T>
T Queue<T>::pop()
{
	T tmp = buffer[0];
	buffer.pop(0);
	return tmp;
}

template<typename T>
void Queue<T>::add(T element)
{
	buffer.add(element);
}

template<typename T>
size_t Queue<T>::size()
{
	return buffer.getSize();
}
