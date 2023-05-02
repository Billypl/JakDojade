#pragma once
#include <iostream>
#include "Node.h"
#include <array>


#pragma once

template<typename List>
class ListIterator
{

public:

	using ValueType = typename List::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

	using ValueNodeType = typename List::NodeType;
	using PointerNodeType = ValueNodeType*;
	using ReferenceNodeType = ValueNodeType&;

public:

	ListIterator(PointerNodeType nodePtr, PointerType ptr)
		: nodePtr(nodePtr), ptr(ptr) {}

	ListIterator& operator++();
	ListIterator operator++(int);
	ListIterator& operator--();
	ListIterator operator--(int);

	bool operator==(const ListIterator& other) const;
	bool operator!=(const ListIterator& other) const;
	ReferenceType operator*();
	PointerType operator->();

private:

	PointerType ptr;
	PointerNodeType nodePtr;

};



template<typename T, size_t B_SIZE>
class List
{
public:

	using ValueType = T;
	using NodeType = Node<T, B_SIZE>;
	using Iterator = ListIterator<List<T, B_SIZE>>;

private:

	Node<T, B_SIZE>* first;
	Node<T, B_SIZE>* last;
	size_t blocksCount;

public:

	List();
	List(const List& other);
	~List();

	size_t getSize() const;
	void add();
	void add(const T& item);
	void pop();
	void pop(size_t index);

	T& get(size_t index);
	T& getLast();
	T& operator[] (size_t index);
	const T& operator[] (size_t index) const;
	void operator=(const List& other);

	Iterator begin();
	Iterator end();

	void print() const;
	bool isEmpty() const;
	void erease();

	template<typename T, size_t B_SIZE>
	friend std::ostream& operator<<(std::ostream& os, const List<T, BLOCK_SIZE>& list);

private:

	void deleteEmptyNode(Node<T, B_SIZE>* emptyNode);
};

