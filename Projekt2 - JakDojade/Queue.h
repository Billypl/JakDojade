#pragma once
#include "List.h"

template <typename T>
class Queue
{
	List<T, BLOCK_SIZE> buffer;

public:
	
	T beginning();
	T pop();
	void add(T element);
	size_t size();

};

