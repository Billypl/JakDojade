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

	void setupCities();

	void readMap();
	void printMap();

	void loadCities();
	void printCities();

	void readFlights();


private:

	string loadCityName(int i, int j);
	void loadStringGeneral(string& name, int i, int j);
	void loadString(string& name, int i, int j, bool readingTypeFlag);
	bool isPartOfTheName(char ch);
	bool isFirstLetter(int i, int j);
	bool isLastLetter(int i, int j);

public:

	void loadNeighbours();
	bool isRoadPiece(const point& pos);

private:

	City* findCity(const point& pos);
	City* findCity(const string& name);

private:

	bool isInBounds(int i, int j);
	char readChar();
	string readString();
	int readInt();

};

