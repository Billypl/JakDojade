#include "Cities.h"
#include "vector.h"
#include "vector.cpp"
#include <iostream>
#include "pair.cpp"
#include "List.cpp"
#include "Queue.h"
#include "Queue.cpp"
#include "Stack.h"
#include "Stack.cpp"

#define READ_FORWARD true
#define READ_BACKWARD false
//#define DEBUG

using std::cin;
using std::cout;
using std::endl;

void Cities::setupCities()
{
	readMap();
	loadCities();
	loadNeighbours();
	readAndLoadFlights();
	readAndMakeQueries();
}

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

void Cities::readAndLoadFlights()
{
	getchar(); // read enter after the board
	int flightsCount = readInt();
	
	while (flightsCount--)
	{
		string source = readString();
		string destination = readString();
		int time = readInt();

		City* city = findCity(source);
		Neighbour* neighbour = city->findNeighbour(destination);
		if (neighbour != nullptr)
		{
			neighbour->distance = sbl::min(neighbour->distance, time);
		}
		else
		{
			city->neighbours.add(Neighbour(findCity(destination), time));
		}
	}
}

void Cities::readAndMakeQueries()
{
	int queriesCount = readInt();

	while (queriesCount--)
	{
		string source = readString();
		string destination = readString();
		int type = readInt();

		findShortestPath(source, destination, type);
	}
}

void Cities::findShortestPath(const string& startingCity, const string& endingCity, bool showPath)
{
	if (startingCity == endingCity)
	{
		cout << 0 << endl;
		return;
	}

	struct Vertex
	{
		City* currCity;
		City* prevCity = nullptr;
		int distance = INT_MAX;
		bool isVisited = false;
	};
	vector<Vertex> citiesTable(cities.size());
	for (int i = 0; i < cities.size(); i++)
	{
		citiesTable[i].currCity = &cities[i];
	}
	auto findVertexByName = [&](const string& cityName)
	{
		auto city = findCity(cityName);
		for (Vertex& vertex : citiesTable)
		{
			if (vertex.currCity == city)
			{
				return &vertex;
			}
		}
		throw "No city found";
	};
	auto findVertexByCity = [&](City* city)
	{
		for (Vertex& vertex : citiesTable)
		{
			if (vertex.currCity == city)
			{
				return &vertex;
			}
		}
		throw "No city found";
	};

	Queue<Vertex*> queue;
	Vertex* src = findVertexByName(startingCity);
	Vertex* dst = findVertexByName(endingCity);
	src->isVisited = true;
	src->distance = 0;
	queue.add(src);

	while (queue.size() > 0)
	{
		Vertex* v = queue.pop();
		for (Neighbour neighbour : v->currCity->neighbours)
		{
			Vertex* ngb = findVertexByName(neighbour.city->name);
			int newDistance = v->distance + neighbour.distance;
			if (newDistance < ngb->distance)
			{
				ngb->distance = newDistance;
				ngb->prevCity = v->currCity;
			}
			if (!ngb->isVisited)
			{
				queue.add(ngb);
				ngb->isVisited = true;
			}
		}
		//cout << v->currCity->name << endl;
	}

	cout << dst->distance;
	if (showPath == true)
	{
		vector<City*> path;
		while (dst->currCity != src->currCity)
		{
			path.add(dst->currCity);
			dst = findVertexByCity(dst->prevCity);
		}
		vector<City*>::Iterator city = path.end();
		while (--city != path.begin())
		{
			cout << " " << (*city)->name;
		}
	}
	cout << endl;
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
			int distance = queue.beginning().second;
			point p = queue.beginning().first;
			queue.pop();

			isVisited[p.x][p.y] = true;
			if (map[p.x][p.y] == '*' && p != city.pos)
			{
				city.neighbours.add(Neighbour(findCity(p), distance + 1));
				continue;
			}
			for (auto& offset : combinations)
			{
				point nieghbour(p + offset);
				if (isInBounds(p.x, p.y) && isRoadPiece(nieghbour) && !isVisited[nieghbour.x][nieghbour.y])
				{
					queue.add({ nieghbour, distance + 1 });
				}
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
	return &cities[findCityIndex(pos)];
}

City* Cities::findCity(const string& name)
{
	for (auto& city : cities)
	{
		if (city.name == name)
		{
			return &city;
		}
	}
	throw "No city found!";
	return nullptr;
}

int Cities::findCityIndex(const point& pos)
{
	for (int i = 0; i < cities.size(); i++)
	{
		if (cities[i].pos == pos)
		{
			return i;
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
	throw "Invalid city collocation";
	return name;
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

string Cities::readString()
{
	char ch = getchar();
	string str;
	while (ch != '\n' && ch != ' ')
	{
		str += ch;
		ch = getchar();
	}
	return str;
}


int Cities::readInt()
{
	int number = 0, c;
	do {
		c = getchar();
		if (c >= '0' && c <= '9')
		{
			number = number * 10 + (c - '0');
		}
	} while (c != '\n');
	return number;
}

bool Cities::isInBounds(int i, int j)
{
	return  i >= 0
		 && j >= 0
		 && i < map.size()
		 && j < map[0].size();
}


