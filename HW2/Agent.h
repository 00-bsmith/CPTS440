// Agent.h

#ifndef AGENT_H
#define AGENT_H

#include "Action.h"
#include "Percept.h"
#include <stdlib.h>//so i have access to rand

class Agent
{
public:
	Agent ();
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept);
	void GameOver (int score);
	
	int x;
	int y;
	int facing; //0, 1, 2, 3
	/* 0
	3    1
	   2
	*/
	int hasGold; //0 for no gold, and 1 for gold
	int shot;//0 for not shot, 1 for has shot
};

#endif // AGENT_H
