#include "Planet.h"
#include "Galaxy.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <utility>
#include <algorithm>
#include <cfloat>

Galaxy::Galaxy(std::string filename){
	this->numPlanets = 0;
	std::ifstream reader;
	std::string x;
	reader.open(filename,std::fstream::in);
	while(std::getline(reader, x)){
		std::string name;
		std::string xCord;
		std::string yCord;
		std::string zCord;
		int space1 = x.find(' ');
		int space2 = x.find(' ', space1+1);
		int space3 = x.find(' ', space2+1);
		name = x.substr(0, space1);
		xCord = x.substr(space1, space2);
		yCord = x.substr(space2, space3);
		zCord = x.substr(space3);
		Planet * p = new Planet(name, atol(xCord.c_str()), atol(yCord.c_str()), atol(zCord.c_str()));
		this->planets.push_back(p);//planets is a vector containing all of the planets in the file
		numPlanets++;
	}
	reader.close();
	std::vector<std::pair<long, Planet*>> temp;
	for(auto i : this->planets){
		for(auto j : this->planets){
				std::pair <long, Planet*> planet = std::make_pair(distance(i,j), j);
				temp.push_back(planet);
		}
		std::vector<std::pair<long, Planet*>> sorted = Galaxy::sort(temp); //sorts the distances for each planet
		for(int k = 1; k < 5; k++){
			i->adj.push_back(sorted.at(k).second);
		}
		temp.clear();
	}
}

unsigned int Galaxy::size(){
	return numPlanets;
}

long Galaxy::distance(Planet* a, Planet* b){
	long xDistance2=std::pow((b->getXCoor()-a->getXCoor()),2);
	long yDistance2=std::pow((b->getYCoor()-a->getYCoor()),2);
	long zDistance2=std::pow((b->getZCoor()-a->getZCoor()),2);
	long sum=xDistance2+yDistance2+zDistance2;
	return std::pow(sum,0.5);

}

Planet * Galaxy::findByName(std::string planetName){
	for(auto i : this->planets){
		if(i->getName() == planetName)return i;
	}
	return NULL;
}

std::vector<Planet *> Galaxy::shortestPath(Planet * start, Planet * dest){
	std::vector<Planet *> retVec;
	start->dist = 0;
	Planet * curr = start;
	for(int i = 0; i < (int)this->planets.size(); i++){
		for(auto j : curr->adj){
			if(distance(curr,j) + curr->dist < j->dist){
				j->dist = curr->dist + distance(curr,j);
				j->prev = curr;
			}
		}
		curr->visited = true;
		curr = Galaxy::minVertex();
		if(curr == nullptr) break;
	}
	curr = dest;
	retVec.insert(retVec.begin(), dest);
	while(curr->prev != nullptr){
			retVec.insert(retVec.begin(), curr->prev);
			curr = curr->prev;
	}
	if(retVec.front()->getName() == dest->getName() && retVec.front()->getName() != start->getName()) retVec.clear();
	return retVec;
}

Planet * Galaxy::minVertex(){
	Planet * retVal = nullptr;
	long double min = LDBL_MAX;
	for(auto p : this->planets){
		if(p->dist < min && p->visited == false) retVal = p;
	}
	return retVal;
}

Galaxy::~Galaxy(){
	for(auto i : this->planets){
		delete i;
	}
}


double Galaxy::pathDistance(Planet * start, Planet * dest){
	std::vector<Planet*> temp = Galaxy::shortestPath(start,dest);
	if(temp.empty()) return LDBL_MAX; //if theres no path
	double retVal = 0;
	for(int i = 0; i < (int)temp.size() - 1; i++){
		double t = (double)distance(temp.at(i), temp.at(i+1));
		retVal += t;
	}
	if(retVal == 0) return 0;
	return retVal + 2;
}

std::vector<std::pair<long, Planet*>> Galaxy::sort(std::vector<std::pair<long, Planet*>> arr){
   int i, j;
   bool swapped;
   for (i = 0; i < (int)arr.size()-1; i++)
   {
     swapped = false;
     for (j = 0; j < (int)arr.size()-i-1; j++)
     {
        if (arr.at(j).first > arr.at(j+1).first)
        {
           std::swap(arr.at(j), arr.at(j+1));
           swapped = true;
        }
     }
     if (swapped == false)
        break;
   }
   return arr;
}
