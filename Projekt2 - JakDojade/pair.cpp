#include "pair.h"
#include "algorithm.h"
#include <iostream>

template<typename T1, typename T2>
pair<T1, T2>::pair(T1 first, T2 second)
	: first(first), second(second) {}

template<typename T1, typename T2>
void pair<T1, T2>::operator=  (const pair<T1, T2>& other)
{
	first = other.first;
	second = other.second;
}

template<typename T1, typename T2>
bool pair<T1, T2>::operator==(const pair<T1, T2>& other) const
{
	return isEqual(other);
}

template<typename T1, typename T2>
bool pair<T1, T2>::operator!=(const pair<T1, T2>& other) const
{
	return !isEqual(other);
}

template<typename T1, typename T2>
bool pair<T1, T2>::isEqual(const pair<T1, T2>& other) const
{
	return (first == other.first) && (second == other.second);
}

template<typename T1, typename T2>
void pair<T1, T2>::swap(pair<T1, T2>& other)
{
	sbl::swap(first, other.first);
	sbl::swap(second, other.second);
}

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const pair<T1, T2>& p)
{
	std::cout << "(" << p.first << "," << p.second << ")";
	return os;
}

