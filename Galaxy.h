#ifndef MD_GALAXY
#define MD_GALAXY
#include <string>
#include <vector>
#include <utility>
#include "Planet.h"
class Galaxy{
public:
	~Galaxy();
	Galaxy(std::string filename);
	unsigned int size();
	std::vector<std::pair<long, Planet*>> sort(std::vector<std::pair<long, Planet*>>);
	long distance(Planet* a, Planet* b);
	Planet * findByName(std::string planetName);
	std::vector<Planet *> shortestPath(Planet * start, Planet * dest);
	double pathDistance(Planet * start, Planet * dest);
	Planet * minVertex();
private:
	int numPlanets;
	std::vector<Planet*> planets;
};

#endif
