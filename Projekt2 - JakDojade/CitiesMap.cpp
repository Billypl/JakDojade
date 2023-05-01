#include "CitiesMap.h"
#include <iostream>
#include "vector.cpp"
#include "pair.cpp"

#define READ_FORWARD true
#define READ_BACKWARD false

using std::cin;
using std::cout;
using std::endl;

void CitiesMap::readMap()
{
	int w, h;
	cin >> w >> h;
	map.resize(w);
	map.fill(vector<char>(h));

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			map[i][j] = readChar();

	/*
	
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
	
3 3
MAN
.*.
...


	*/

}

void CitiesMap::printMap()
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

void CitiesMap::loadCities()
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

string CitiesMap::loadCityName(int i, int j)
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

void CitiesMap::loadStringGeneral(string& name, int i, int j)
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

void CitiesMap::loadString(string& name, int i, int j,  bool readingTypeFlag)
{
	while (isInBounds(i, j) && isPartOfTheName(map[i][j]))
	{
		name += map[i][j];
		if (readingTypeFlag == READ_FORWARD)
		{
			j++;
		}
		else
		{
			j--;
		}
	}
}

bool CitiesMap::isPartOfTheName(char ch)
{
	return ch != '*' && ch != '#' && ch != '.';
}

bool CitiesMap::isFirstLetter(int i, int j)
{
	return !isInBounds(i - 1, j) ||
		isInBounds(i - 1, j) && !isPartOfTheName(map[i - 1][j]);
}

bool CitiesMap::isLastLetter(int i, int j)
{
	return !isInBounds(i + 1, j) ||
		isInBounds(i + 1, j) && !isPartOfTheName(map[i + 1][j]);
}

void CitiesMap::printCities()
{
	for (int i = 0; i < cities.size(); i++)
		cout << cities[i].name << ": " << cities[i].pos.x << "," << cities[i].pos.y << endl;
}

char CitiesMap::readChar()
{
	char ch = (char)getchar();
	while (ch == ' ' || ch == '\n')
		ch = (char)getchar();
	return ch;
}

bool CitiesMap::isInBounds(int i, int j)
{
	return  i >= 0
		 && j >= 0
		 && i < map.size()
		 && j < map[0].size();
}


