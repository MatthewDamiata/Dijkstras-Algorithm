#include <string>
#include <iostream>
#include <cassert>
#include <list>
#include <cfloat>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>/* timeval, gettimeofday() */
#include "Galaxy.h"
#include "Galaxy.h"
#include "Planet.h"
#include "Planet.h"
using namespace std;

#define PROFILE_RUNS 100

void checkAdjacencies(Galaxy &map, string planet, vector<string> &adjacents){
    list<Planet*> adj, test;
    test = map.findByName(planet)->getAdjacent();
    assert(test.size() == adjacents.size());
    test.sort();
    for(auto a: adjacents){
        adj.push_back(map.findByName(a));
    }
    adj.sort();
    auto a = adj.begin();
    auto t = test.begin();
    for(; a != adj.end() && t != test.end(); a++, t++){
        assert((*a)->getName() == (*t)->getName());
    }
}

void checkPath(Galaxy &map, vector<string> &cities, string start, string dest){
    Planet * startc = map.findByName(start);
    Planet * destc = map.findByName(dest);
    vector<Planet *> route = map.shortestPath(startc, destc);
    assert(route.size() == cities.size());
    int i = 0;
    for(auto r: route){
        assert(r->getName() == cities.at(i));
        i++;
    }
}

int main(int argc, char *argv[]){
    #ifndef TEST0
    {
        cerr << "\n\tTEST #0: Read file of Planets and build your adjacency list (for testing)" << endl;
        Galaxy map("planetsA.dat");
        //Although not required, a print function that prints each point and its adjacencies would make developing your adjacency lists easier
        //map.printPlanets();
        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST1
    {
        cerr << "\n\tTEST #1: Testing Galaxy and Planet Interface" << endl;
        //Test Galaxy class interface
        Galaxy map("planetsB.dat");
        assert(map.size() == 11);

        assert(map.findByName("Kepler-1049b") != NULL);
        assert(map.findByName("HAT-P-27b") != NULL);
        assert(map.findByName("HD116029b") != NULL);
        assert(map.findByName("WASP-21b") != NULL);
        assert(map.findByName("GJ649b") != NULL);
        assert(map.findByName("BD+144559b") != NULL);
        assert(map.findByName("XO-3b") != NULL);
        assert(map.findByName("CoRoT-9b") != NULL);
        assert(map.findByName("CMab") != NULL);
        assert(map.findByName("NotAPlanet") == NULL);

        //Test planet class interface
        assert(map.findByName("Kepler-1049b")->getName() == "Kepler-1049b");
        assert(map.findByName("K2-3b")->getXCoor() == 25 &&
			map.findByName("K2-3b")->getYCoor() == 11 &&
            map.findByName("K2-3b")->getZCoor() == -19
		);
        assert(map.findByName("upsilon")->getXCoor() == 25 &&
            map.findByName("upsilon")->getYCoor() == 11 &&
            map.findByName("upsilon")->getZCoor() == 0
        );
        //assert(map.findByName("upsilon")->distanceBetween(map.findByName("K2-3b")) == 19.0);
        assert(map.findByName("upsilon")->getAdjacent().size() == 4);

        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST2
    {
        cerr << "\n\tTEST #2: Test Adjacencies" << endl;
        Galaxy map("planetsB.dat");
        string planet = "Kepler-1049b";
        vector<string> adjacents = {"HAT-P-27b", "BD+144559b", "WASP-21b", "XO-3b"};
        checkAdjacencies(map, planet, adjacents);

        planet = "HAT-P-27b";
        adjacents = {"Kepler-1049b","BD+144559b","XO-3b","upsilon"};
        checkAdjacencies(map, planet, adjacents);

        planet = "HD116029b";
        adjacents = {"CMab","CoRoT-9b","WASP-21b","upsilon"};
        checkAdjacencies(map, planet, adjacents);

        planet = "WASP-21b";
        adjacents = {"Kepler-1049b","CoRoT-9b","HD116029b","XO-3b"};
        checkAdjacencies(map, planet, adjacents);

        planet = "GJ649b";
        adjacents = {"Kepler-1049b","HAT-P-27b","BD+144559b","XO-3b"};
        checkAdjacencies(map, planet, adjacents);

        planet = "BD+144559b";
        adjacents = {"Kepler-1049b","HAT-P-27b","upsilon","XO-3b"};
        checkAdjacencies(map, planet, adjacents);

        planet = "CoRoT-9b";
        adjacents = {"CMab","XO-3b","HD116029b","WASP-21b"};
        checkAdjacencies(map, planet, adjacents);

        planet = "XO-3b";
        adjacents = {"Kepler-1049b","HAT-P-27b","BD+144559b","WASP-21b"};
        checkAdjacencies(map, planet, adjacents);

        planet = "CMab";
        adjacents = {"CoRoT-9b","upsilon","HD116029b","K2-3b"};
        checkAdjacencies(map, planet, adjacents);

        planet = "K2-3b";
        adjacents = {"upsilon","HAT-P-27b","HD116029b","XO-3b"};
        checkAdjacencies(map, planet, adjacents);

        planet = "upsilon";
        adjacents = {"CMab","HAT-P-27b","K2-3b","XO-3b"};
        checkAdjacencies(map, planet, adjacents);

        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST3
    {
        Galaxy map("planetsB.dat");
        cerr << "\n\tTEST #3: Simple Shortest Path" << endl;
        vector<string> path = {"CMab","HD116029b"};
        checkPath(map, path, "CMab", "HD116029b");

        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST4
    {
        cerr << "\n\tTEST #4: Less Simple Shortest Path" << endl;
        Galaxy map("planetsB.dat");
        vector<string> path = {"HAT-P-27b","upsilon", "K2-3b"};
        checkPath(map, path, "HAT-P-27b", "K2-3b");
        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST5
    {
        cerr << "\n\tTEST #5: Shortest Path between a single point" << endl;
        Galaxy map("planetsB.dat");
        vector<string> path = {"GJ649b"};
        checkPath(map, path, "GJ649b", "GJ649b");
        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST6
    {
        cerr << "\n\tTEST #6: Shortest Path with multiple midpoints" << endl;
        Galaxy map("planetsB.dat");
        vector<string> path = {"HAT-P-27b", "upsilon", "K2-3b", "HD116029b"};
        checkPath(map, path, "HAT-P-27b", "HD116029b");

        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST7
    {
        cerr << "\n\tTEST #7: Shortest Path with more edges" << endl;
        Galaxy map("planetsB.dat");
        vector<string> path = {"GJ649b", "HAT-P-27b", "upsilon", "K2-3b"};
        checkPath(map, path, "GJ649b", "K2-3b");

        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST8
    {
        cerr << "\n\tTEST #8: No Path" << endl;
        Galaxy map("planetsB.dat");
        vector<string> path;
        checkPath(map, path, "CMab", "GJ649b");

        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST9
    {
        cerr << "\n\tTEST #9: Distance of no path is inf" << endl;
        Galaxy map("planetsB.dat");
        Planet * start = map.findByName("XO-3b");
        Planet * stop = map.findByName("GJ649b");
        assert(isinf(map.pathDistance(start, stop)));

        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST10
    {
        cerr << "\n\tTEST #10: Distance from a single planet (should be 0)" << endl;
        Galaxy map("planetsB.dat");
        Planet * start = map.findByName("K2-3b");
        Planet * stop = map.findByName("K2-3b");
        assert(map.pathDistance(start, stop) == 0);

        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST11
    {
        cerr << "\n\tTEST #11: Distance between two planets" << endl;
        Galaxy map("planetsB.dat");
        Planet * start = map.findByName("Kepler-1049b");
        Planet * stop = map.findByName("K2-3b");
        assert(round(map.pathDistance(start, stop)) == 91.0);

        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST12
    {
        cerr << "\n\tTEST #12: Distance with two equal paths" << endl;
        Galaxy map("planetsB.dat");
        Planet * start = map.findByName("BD+144559b");
        Planet * stop = map.findByName("HD116029b");
        assert(round(map.pathDistance(start, stop)) == 117.0);
        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
    #ifndef TEST13
    {
        cerr << "\n\tTEST #13: Shortest Path Performance" << endl;
        vector<string> path = {"HD116029b", "CoRoT-9b", "XO-3b", "BD+144559b"};
        cerr << "\tBeginning profile time" << endl;
        double average_time = 0;
        struct timeval start_t, stop_t;
        for(int i = 0; i < PROFILE_RUNS; i++){
            Galaxy map("planetsB.dat");
            gettimeofday(&start_t, NULL);
            checkPath(map, path, "HD116029b", "BD+144559b");
            gettimeofday(&stop_t, NULL);
            time_t start_time = (start_t.tv_sec* 1000000) + start_t.tv_usec;
            time_t stop_time = (stop_t.tv_sec* 1000000) + stop_t.tv_usec;
            double profile_time = stop_time - start_time;
            average_time += profile_time;
        }
        printf("\tCompleted profile time = %lf\n", average_time/PROFILE_RUNS);

        cerr << "\n\t========================PASS========================\n" << endl;
    }
    #endif
}
