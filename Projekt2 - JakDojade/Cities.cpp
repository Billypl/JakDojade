#include "Cities.h"
#include <iostream>
#include "pair.cpp"
#include "Queue.h"
#include "Queue.cpp"
#include "vector.h"
#include "vector.cpp"


#define READ_FORWARD true
#define READ_BACKWARD false
#define DEBUG

using std::cin;
using std::cout;
using std::endl;

void Cities::readMap()
{
	int w, h;
	cin >> w >> h;
	map.resize(h);
	map.fill(vector<char>(w));

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			char ch = readChar();
			map[i][j] = ch;
			if (ch == '*')
			{
				cities.add(City(point(i, j)));
			}
		}
	}
}

void Cities::printMap()
{
	for (auto& row : map)
	{
		for (auto& tile : row)
		{
			cout << tile;
		}
		cout << endl;
	}
}

void Cities::loadCities()
{
	for (auto& city : cities)
	{
		city.name = loadCityName(city.pos.x, city.pos.y);
	}
}

void Cities::printCities()
{
	for (auto& city : cities)
	{
		cout << city.name << ": " << city.pos.x << "," << city.pos.y << endl;

		auto& neighbours = city.neighbours;
		if (!neighbours.isEmpty())
		{
			cout << "Neighbours: \n";
			for (int j = 0; j < neighbours.size(); j++)
			{
				cout << " " << j << ". Name: " << neighbours[j].city->name << " distance: " << neighbours[j].distance << endl;
			}
		}
	}
}

void Cities::loadNeighbours()
{
	vector<point> combinations;
	combinations.add(
		point(-1, 0),
		point(0, 1),
		point(1, 0),
		point(0, -1)
	);

	for (auto& city : cities)
	{
		vector<vector<bool>> isVisited(map.size(), vector<bool>(map[0].size(), false));
		Queue<pair<point, int>> queue;

		queue.add({ city.pos, -1 });
		while (queue.size() > 0)
		{
			auto firstInQueue = queue.pop();
			point p = firstInQueue.first;
			isVisited[p.x][p.y] = true;
			for (auto& offset : combinations)
			{
				point nieghbour(p + offset);
				if (isInBounds(p.x, p.y) && isRoadPiece(nieghbour) && !isVisited[nieghbour.x][nieghbour.y])
				{
					queue.add({ nieghbour, firstInQueue.second + 1 });
				}
			}
			if (map[p.x][p.y] == '*' && p != city.pos)
			{
				city.neighbours.add(Neighbour(findCity(p), firstInQueue.second + 1));
			}
		}
	}
}

bool Cities::isRoadPiece(const point& pos)
{
	return isInBounds(pos.x, pos.y) && (map[pos.x][pos.y] == '#'  || map[pos.x][pos.y] == '*');
}

City* Cities::findCity(const point& pos)
{
	for (auto& city : cities)
	{
		if (city.pos == pos)
		{
			return &city;
		}
	}
	throw "No city found";
}

string Cities::loadCityName(int i, int j)
{
	string name;
	for (int a = -1; a <= 1; a++)
	{
		for (int b = -1; b <= 1; b++)
		{
			if (isFirstLetter(i + a, j + b) || isLastLetter(i + a, j + b))
			{
				loadStringGeneral(name, i + a, j + b);
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
#ifdef DEBUG
		map[i][j] = '.';
#endif // DEBUG
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


