#pragma once
#include "string.h"
#include "vector.h"
#include "point.h"

class City;

class Neighbour
{

public:

	City* city;
	int distance;
	Neighbour() {}
	Neighbour(City* city) 
		: city(city) {}
	Neighbour(int distance)
		: distance(distance) {}
	Neighbour(City* city, int distance)
		: city(city), distance(distance) {}

};

class City
{

public:

	string name;
	point pos;
	vector<Neighbour> neighbours;
	City() {};
	City(point position)
		: pos(position) {}
	City(string name, point position)
		: name(name), pos(position) {}

};

