#include "Cities.h"
#include <iostream>
#include "vector.cpp"
#include "pair.cpp"

#define READ_FORWARD true
#define READ_BACKWARD false

using std::cin;
using std::cout;
using std::endl;

void Cities::readMap()
{
	int w, h;
	cin >> w >> h;
	map.resize(w);
	map.fill(vector<char>(h));

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			map[i][j] = readChar();
}

void Cities::printMap()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}

void Cities::loadCities()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j] == '*')
			{
				City city(loadCityName(i, j), point(i, j));
				cities.add(city);
			}
		}
	}
}

string Cities::loadCityName(int i, int j)
{
	string name;
	const int tab[] = { -1, 0, 1 }; 
	const int tabSize = 3;
	for (int a = 0; a < tabSize; a++)
	{
		for (int b = 0; b < tabSize; b++)
		{
			if (isFirstLetter(i + tab[a], j + tab[b]) || isLastLetter(i + tab[a], j + tab[b]))
			{
				loadStringGeneral(name, i + tab[a], j + tab[b]);
				return name;
			}
		}
	}
}

void Cities::loadStringGeneral(string& name, int i, int j)
{
	if (isFirstLetter(i, j))
	{
		loadString(name, i, j, READ_FORWARD);
	}
	else if (isLastLetter(i, j))
	{
		loadString(name, i, j, READ_BACKWARD);
		name.reverse();
	}
}

void Cities::loadString(string& name, int i, int j,  bool readingTypeFlag)
{
	while (isInBounds(i, j) && isPartOfTheName(map[i][j]))
	{
		name += map[i][j];
		j += readingTypeFlag == READ_FORWARD ? 1 : -1;
	}
}

bool Cities::isPartOfTheName(char ch)
{
	return ch != '*' && ch != '#' && ch != '.';
}

bool Cities::isFirstLetter(int i, int j)
{
	return isInBounds(i, j) && isPartOfTheName(map[i][j]) &&
		(!isInBounds(i, j - 1) || !isPartOfTheName(map[i][j - 1]));
}

bool Cities::isLastLetter(int i, int j)
{
	return isInBounds(i, j) && isPartOfTheName(map[i][j]) &&
		(!isInBounds(i, j + 1) || !isPartOfTheName(map[i][j + 1]));
}

void Cities::printCities()
{
	for (int i = 0; i < cities.size(); i++)
		cout << cities[i].name << ": " << cities[i].pos.x << "," << cities[i].pos.y << endl;
}

char Cities::readChar()
{
	char ch = (char)getchar();
	while (ch == ' ' || ch == '\n')
		ch = (char)getchar();
	return ch;
}

bool Cities::isInBounds(int i, int j)
{
	return  i >= 0
		 && j >= 0
		 && i < map.size()
		 && j < map[0].size();
}


