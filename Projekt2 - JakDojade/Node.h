#pragma once
#define BLOCK_SIZE 8


template<typename T, size_t B_SIZE>
class Node
{
public:
	T items[B_SIZE];
	bool filled[B_SIZE];
	size_t size = 0;
	Node* prev = nullptr;
	Node* next = nullptr;

	size_t findLastFilledIndex();
	T& getLast();

	void add(const T& item);
	T& operator[] (size_t index);
	void pop();
	Node();

	size_t findMappedIndex(size_t index);

};



