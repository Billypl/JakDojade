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
	City(string name, point position)
		: name(name), pos(position) {}

};

