#include <iostream>
#include "algorithm.h"
#include "pair.h"
#include "pair.cpp"
#include "point.h"
#include "vector.h"
#include "vector.cpp"
#include "string.h"

#include "CitiesMap.h"

using std::cout;
using std::endl;

int main()
{
	CitiesMap citiesMap;
	citiesMap.readMap();
	citiesMap.loadCities();

	cout << endl;
	//citiesMap.printMap();
	citiesMap.printCities();

}