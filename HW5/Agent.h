// Agent.h

#ifndef AGENT_H
#define AGENT_H

#include "Action.h"
#include "Percept.h"

#include "Location.h"
#include "Orientation.h"
#include "Search.h"
#include "WorldState.h"
#include <list>

class Agent
{
public:
	Agent();
	~Agent();
	void Initialize();
	Action Process(Percept& percept);
	void GameOver(int score);

	bool agentHasGold;
	list<Action> actionList;
	SearchEngine searchEngine;

	//debug
	int debug_counter;
	//-------------mystuff---------------------
	WorldState myState;


	//Location myLoc; //stored in myState
	//Orientation myOr; //stored in myState
	Location prevLoc;

	//store visited locations
	list<Location> visLoc;
	//safe, unvisited locations
	list<Location> safeLoc; //this way i have a list of places to go to check
	//percept locations

	list<Location> stenchSpot;
	list<Location> breezeSpot;
	//list<Location> pitSpots; //stored in myState
	//Location WumpusSpot; //stored in myState
	//Location goldSpot; //stored in myState

	int xMin = 1;
	int yMin = 1;
	//int worldSize; //we know the world is a square, lets get the size 
	int foundMax;
	//foundMax is going to be set to 1 when a bump happens so we know max is found and to adhere to it
	//until max is found, ignore the stored max value!
	int knowsGold;//adding this as a test
	//for some reason myState.goldLocation is wiping between runs, adding a new storage
	Location newGold;
	//new test, since my int values arent wiping, lets store gold X and Y as ints
	int goldX;
	int goldY;

	bool foundWumpus;
	bool findWumpus(list<Location> stench);

	bool safeSqaure();
};

#endif // AGENT_H
