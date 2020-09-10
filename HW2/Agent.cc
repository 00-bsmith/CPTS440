// Agent.cc

#include <iostream>
#include "Agent.h"

using namespace std;

Agent::Agent ()
{
 x=1;
 y=1;
 facing=1;
 hasGold=0;
 shot=0;
}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{

}

/* Action Agent::Process (Percept& percept)
{
	char c;
	Action action;
	bool validAction = false;

	while (! validAction)
	{
		validAction = true;
		cout << "Action? ";
		cin >> c;
		if (c == 'f') {
			action = GOFORWARD;
		} else if (c == 'l') {
			action = TURNLEFT;
		} else if (c == 'r') {
			action = TURNRIGHT;
		} else if (c == 'g') {
			action = GRAB;
		} else if (c == 's') {
			action = SHOOT;
		} else if (c == 'c') {
			action = CLIMB;
		} else {
			cout << "Huh?" << endl;
			validAction = false;
		}
	}
	return action;
} */

void Agent::GameOver (int score)
{

}
//need to track direction facing, and x,y coordinates
//need a random number generator, 0, 1, 2 for forward, left right
//need a way to start automation (lets have input = a)

Action Agent::Process (Percept& percept)//need to store the state outside of this.
{
	Action action;
	//cout<<"x=:"<<x<<endl;
	//cout<<"y=:"<<y<<endl; 
	//wanted to be sure they initialized right
	
	int move= rand() %3;// 0 will be forward, 1 will be left, 2 will be right
	
	
	if(percept.Glitter==true){
		action=GRAB;
		hasGold=1;
	}
	else if(x==1&&y==1&&hasGold==1){
		action=CLIMB;
	}
	
	//going to add a way to keep track of if i shot or not, this will be a 0 if not shot
	else if(y==4&&facing==1&&shot==0){
		action=SHOOT;
		shot=1;
	}
	else if(x==4&&facing==0&&shot==0){
		action=SHOOT;
		shot=1;
	}
	//now we get to the movement part, this is where rand comes in
	else if(move==0){
		action=GOFORWARD;
		if(facing==0){//up
			if(y!=4){//can't go up more if at 4
			y+=1;
			}
		}
		else if(facing==1){//right
			if(x!=4){
			x+=1;
			}
		}
		else if(facing==2){//down
		if(y!=1){
			y-=1;
		}
		}
		else if(facing==3){//left
			if(x!=1){
			x-=1;
			}
		}
	}
	else if(move==1){//turn left
		action=TURNLEFT;
		if(facing==0){//dont want negatives
			facing=3;
		}
		else{
			facing-=1;
		}
	}
	else if(move==1){//turn right
		action=TURNRIGHT;
		if(facing==3){//3 is cap
			facing=0;
		}
		else{
			facing+=1;
		}
	}
	//remove this later, going to spit out what my stats are for debugging
	//cout<<"X=: "<<x<<endl<<"Y=: "<<y<<endl<<"Facing: "<<facing<<endl;
	
	return action;
}
