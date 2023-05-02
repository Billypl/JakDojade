#pragma once
#include "List.h"

template <typename T>
class Stack
{
	List<T, BLOCK_SIZE> buffer;

public:

	T pop();
	void add(T element);
	size_t size();

};


