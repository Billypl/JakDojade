#pragma once
#include "string.h"
#include "vector.h"
#include "point.h"

class City
{

public:

	string name;
	point pos;
	vector<City*> neighbours;
	City() {};
	City(point position)
		: pos(position) {}
	City(string name, point position)
		: name(name), pos(position) {}

};

