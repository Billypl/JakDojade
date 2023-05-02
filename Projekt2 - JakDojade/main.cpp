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

int main()
{
	Cities cities;
	cities.readMap();
	cities.loadCities();

	cout << endl;
	cities.printCities();
	cities.printMap();

}