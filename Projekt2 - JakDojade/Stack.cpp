#include "Stack.h"

template<typename T>
T Stack<T>::pop()
{
	T tmp = buffer.getLast();
	buffer.pop();
	return tmp;
}

template<typename T>
void Stack<T>::add(T element)
{
	buffer.add(element);
}

template<typename T>
size_t Stack<T>::size()
{
	return buffer.getSize();
}
