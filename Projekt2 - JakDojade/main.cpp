#include <iostream>
#include "algorithm.h"
#include "pair.h"
#include "pair.cpp"
#include "point.h"
#include "vector.h"
#include "vector.cpp"
#include "string.h"

#include "Cities.h"

using std::cout;
using std::endl;

#include <chrono>
using namespace std::chrono;

void measureTime()
{
	
	auto start = high_resolution_clock::now();
	// insert function here
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(stop - start);

	cout << "Time taken by function: "
		<< (duration.count() + 0.0) / 1000 << " microseconds" << endl;

}

int main()
{
	measureTime();
	Cities cities;
	cities.readMap();
	cities.loadCities();

	//cities.printCities();
	//cities.printMap();

}