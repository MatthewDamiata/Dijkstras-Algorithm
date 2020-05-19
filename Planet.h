#ifndef MD_PLANET
#define MD_PLANET
#include <string>
#include <vector>
#include <list>

class Planet{
public:
	Planet(std::string planetName, long xCoor, long yCoor, long zCoor);
	std::string getName();
	long getXCoor();
	long getYCoor();
	long getZCoor();
	Planet * prev;
	long double dist;
	bool visited;
	std::list<Planet*> getAdjacent();
	std::list<Planet*> adj;

private:
	long xCoor;
	long yCoor;
	long zCoor;
	std::string name;
	//std::list<Planet*> adj;
};

#endif
