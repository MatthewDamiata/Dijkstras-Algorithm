#include "Planet.h"
#include <vector>
#include <string>
#include <list>
#include <cfloat>

Planet::Planet(std::string planetName, long xCoor, long yCoor, long zCoor){
	this->name = planetName;
	this->xCoor = xCoor;
	this->yCoor = yCoor;
	this->zCoor = zCoor;
	this->visited = false;
	this->prev = nullptr;
	this->dist = LDBL_MAX;
}

std::string Planet::getName(){
	return this->name;
}

long Planet::getXCoor(){
	return this->xCoor;
}

long Planet::getYCoor(){
	return this->yCoor;
}

long Planet::getZCoor(){
	return this->zCoor;
}

std::list<Planet*> Planet::getAdjacent(){
	return this->adj;
}
