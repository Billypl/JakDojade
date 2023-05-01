#pragma once
#include "vector.h"
#include "pair.h"
#include "point.h"
#include "string.h"
#include "City.h"

class Cities
{

public:

	vector<vector<char>> map;
	vector<City> cities;

	void readMap();
	void printMap();
	void loadCities();
	void printCities();
private:
	string loadCityName(int i, int j);
	void loadStringGeneral(string& name, int i, int j);
	void loadString(string& name, int i, int j, bool readingTypeFlag);
	bool isPartOfTheName(char ch);
	bool isFirstLetter(int i, int j);
	bool isLastLetter(int i, int j);
	

private:

	char readChar();
	bool isInBounds(int i, int j);

};

