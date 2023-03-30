// Agent.cc
//
// This code works only for the testworld that comes with the simulator.

#include <iostream>
#include <list>
#include "Agent.h"

using namespace std;

Agent::Agent ()
{

}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{
	// Works only for test world.
	// You won't initially know safe locations or world size.
	//for (int x = 1; x <= 4; x++) {
	//	for (int y = 1; y <= 4; y++) {
	//		searchEngine.AddSafeLocation(x,y);
	//	}
	//}
	//searchEngine.RemoveSafeLocation(1,3); // wumpus
	//searchEngine.RemoveSafeLocation(3,1); // pit
	//searchEngine.RemoveSafeLocation(3,3); // pit
	//searchEngine.RemoveSafeLocation(4,4); // pit
	searchEngine.AddSafeLocation(1, 1); // we know 1,1 will always be safe
	//initial position
	myState.agentLocation.X = 1;
	myState.agentLocation.Y = 1;
	myState.agentOrientation = RIGHT;

	prevLoc.X = 0;
	prevLoc.Y = 0;

	visLoc.push_back(myState.agentLocation);
	//safeLoc.push_back(myState.agentLocation);//safe is for unvisited, dont need to add it

	myState.agentHasGold = false;
	myState.agentHasArrow = true;


	agentHasGold = false;
	actionList.clear();
	

	//debug
	debug_counter = 0;

	


}

Action Agent::Process (Percept& percept)
{
	list<Action> actionList2;
	/*if (debug_counter < 6) {
		debug_counter++;*/
		//version 2
		//lets percept scan before we enter the if empty
		//cout << "Beginning Cycle" << endl << "Location: " << myState.agentLocation.X << "," << myState.agentLocation.Y << endl;
		if (percept.Glitter == true) {
			//clear our list, grab gold, and head to home and climb
		//	cout << "Gold was found" << endl;
			actionList.clear();
			actionList2.clear();
			myState.goldLocation = myState.agentLocation;//original
			newGold.X = myState.agentLocation.X;//attempt 2
			newGold.Y = myState.agentLocation.Y;
			goldX = myState.agentLocation.X;//attempt 3
			goldY= myState.agentLocation.Y;
			//cout << "Gold is at: " << myState.goldLocation.X << "," << myState.goldLocation.Y << endl;
			knowsGold = 1;

			//myState.agentHasGold = true;//i dont use this
			agentHasGold = true;

			actionList.push_back(GRAB);
			actionList2 = searchEngine.FindPath(myState.agentLocation, myState.agentOrientation, Location(1, 1), RIGHT);
			actionList.splice(actionList.end(), actionList2);
			actionList.push_back(CLIMB);
		}
		if (percept.Stench == true) {
			stenchSpot.push_back(myState.agentLocation);
		}
		if (percept.Breeze == true) {
			breezeSpot.push_back(myState.agentLocation);
		}
		if (percept.Bump == true) {
			actionList.clear();
			actionList2.clear();
			if (myState.agentOrientation == UP) {
				myState.agentLocation.Y -= 1;
				myState.worldSize = myState.agentLocation.Y;
				foundMax = 1;
			}
			if (myState.agentOrientation == RIGHT) {
				myState.agentLocation.X -= 1;
				myState.worldSize = myState.agentLocation.X;
				foundMax = 1;
			}
		}

		if ((percept.Breeze == false) && percept.Stench == false) {
			//lets update the spots around us!
				//Copied from the original version


				//we know adjacent spots work
			//cout << "Adding spots to safety" << endl;
			searchEngine.AddSafeLocation(myState.agentLocation.X + 1, myState.agentLocation.Y);//new 1 (X+1, Y)
			//cout << "New safe:" << endl << "X: " << myState.agentLocation.X + 1 << " Y: " << myState.agentLocation.Y << endl;
			//going to add an if to stop it from adding a x=0 possibility
			if (myState.agentLocation.X - 1 > 0) {
				searchEngine.AddSafeLocation(myState.agentLocation.X - 1, myState.agentLocation.Y);//new 2 (X-1, Y)
			//	cout << "New safe:" << endl << "X: " << myState.agentLocation.X - 1 << " Y: " << myState.agentLocation.Y << endl;
			}
			searchEngine.AddSafeLocation(myState.agentLocation.X, myState.agentLocation.Y + 1);//new 3 (X, Y+1)
			//cout << "New safe:" << endl << "X: " << myState.agentLocation.X << " Y: " << myState.agentLocation.Y + 1 << endl;
			if (myState.agentLocation.Y - 1 > 0) {
				searchEngine.AddSafeLocation(myState.agentLocation.X, myState.agentLocation.Y - 1);//new 4 (X, Y-1)
		//		cout << "New safe:" << endl << "X: " << myState.agentLocation.X << " Y: " << myState.agentLocation.Y - 1 << endl;
			}

			list<Location>::iterator it;
			int match = 0;
			int match2 = 0;
			//cout << "IT 1" << endl;
			for (it = visLoc.begin(); it != visLoc.end(); it++) {
				//check if it matches new1
				if ((it->X == myState.agentLocation.X + 1) && (it->Y == myState.agentLocation.Y)) {
					match = 1;
					break;//no need to go through the full list of visited spots
				}


			}
			if (match != 1) {//if we didnt hit a match, add to safeloc not visloc
				//visLoc.push_back(Location(myState.agentLocation.X + 1, myState.agentLocation.Y));
				safeLoc.push_back(Location(myState.agentLocation.X + 1, myState.agentLocation.Y));
			}
			//we have to repeat for the next 3 spots
			///////////////////////////////////////////////////////////////////////////
			//cout << "IT 2" << endl;
			for (it = visLoc.begin(); it != visLoc.end(); it++) {
				//check if it matches new1
				if ((it->X == myState.agentLocation.X - 1) && (it->Y == myState.agentLocation.Y)) {
					match = 2;
					break;//no need to go through the full list of visited spots
				}
			}
			if (match != 2) {//if we didnt hit a match, add to visloc
				if (myState.agentLocation.X - 1 > 0) {
					safeLoc.push_back(Location(myState.agentLocation.X - 1, myState.agentLocation.Y));
				}
			}
			////////////////////////////////////////////////////////////////////////////
			//cout << "IT 3" << endl;
			for (it = visLoc.begin(); it != visLoc.end(); it++) {
				//check if it matches new1
				if ((it->X == myState.agentLocation.X) && (it->Y == myState.agentLocation.Y + 1)) {
					match = 3;
					break;//no need to go through the full list of visited spots
				}
			}
			if (match != 3) {//if we didnt hit a match, add to visloc
				safeLoc.push_back(Location(myState.agentLocation.X, myState.agentLocation.Y + 1));
			}
			////////////////////////////////////////////////////////////////////////////
			//cout << "IT 4" << endl;
			for (it = visLoc.begin(); it != visLoc.end(); it++) {
				//check if it matches new1
				if ((it->X == myState.agentLocation.X) && (it->Y == myState.agentLocation.Y - 1)) {
					match = 4;
					break;//no need to go through the full list of visited spots
				}
			}
			if (match != 4) {//if we didnt hit a match, add to visloc
				if (myState.agentLocation.Y - 1 > 0) {
					safeLoc.push_back(Location(myState.agentLocation.X, myState.agentLocation.Y - 1));
				}
			}
			////////////////////////////////////////////////////////////////////////////


		}


		//visLoc.push_back(myState.agentLocation);
		searchEngine.AddSafeLocation(myState.agentLocation.X, myState.agentLocation.Y);


		//lets do the wumpus search here
		if (foundWumpus != true) {
			foundWumpus = findWumpus(stenchSpot);
		}
		


		if (actionList.empty()) {
			safeSqaure();
			// Works only for test world (you won't initially know gold location)
			//if (! agentHasGold) {
			//	// Goto (2,3) and GRAB
			//	actionList2 = searchEngine.FindPath(Location(1,1), RIGHT, Location(2,3), RIGHT);
			//	actionList.splice(actionList.end(), actionList2);
			//	actionList.push_back(GRAB);
			//	agentHasGold = true;
			//} else {
			//	// Goto (1,1) and CLIMB
			//	actionList2 = searchEngine.FindPath(Location(2,3), RIGHT, Location(1,1), RIGHT);
			//	actionList.splice(actionList.end(), actionList2);
			//	actionList.push_back(CLIMB);
			//}
			/*(myState.goldLocation.X != 0*/ //this was tried and failed
			if (knowsGold==1) {//we know the location of the gold

			//	cout << "Empty List, Gold Known" << endl;

				list<Location>::iterator it;
				int counter = 1;
				for (it = visLoc.begin(); it != visLoc.end(); it++) {
					searchEngine.AddSafeLocation(it->X, it->Y);
				//	cout << "Counter: " << counter << endl;
					counter++;
				}


				if (!agentHasGold) {//known but dont have gold
				//	cout << "known, don't have gold, going to gold" << endl;
				//	cout << "Gold At:" << goldX << "," << goldY << endl;
					//actionList2 = searchEngine.FindPath(myState.agentLocation, myState.agentOrientation, Location(goldX,goldY), RIGHT);//for some reason on run 2 this spits out no path
					actionList2 = searchEngine.FindPath(Location(1,1), myState.agentOrientation, Location(goldX, goldY), RIGHT);
					actionList.splice(actionList.end(), actionList2);
					actionList.push_back(GRAB);
					agentHasGold = true;
					actionList2 = searchEngine.FindPath(Location(goldX, goldY), myState.agentOrientation, Location(1, 1), RIGHT);
					actionList.splice(actionList.end(), actionList2);
					actionList.push_back(CLIMB);

				}
				else {//known but have gold
					//if we have the gold lets make a path to home
					//this will probably not be needed
				//	cout << "Known and have gold" << endl;
					actionList2 = searchEngine.FindPath(myState.agentLocation, myState.agentOrientation, Location(1, 1), RIGHT);
					actionList.splice(actionList.end(), actionList2);
					actionList.push_back(CLIMB);
				}

			}
			else {//empty list, no gold location known
				//we have updated our location and our percepts
				if (safeLoc.empty() == false) {
				//	cout << "Going to pop front safeLoc" << endl;
					Location newLoc = safeLoc.front();
					//lets set our location to newLoc, add it to safe locations
				//	cout << "Done copying" << endl;
					safeLoc.remove(newLoc);//removing the front safe
					visLoc.push_back(newLoc);//
					//note, swapped to remove() over pop_front as I think i may be getting duplicates in here somehow
				//	cout << "Done popping" << endl;
					//visLoc.push_back(newLoc); //try it moved at start of the move action instead of the end
					actionList2 = searchEngine.FindPath(myState.agentLocation, myState.agentOrientation, newLoc, RIGHT);
				//	cout << "Done searching" << endl;
				//	cout << "Goal Location (" << newLoc.X << "," << newLoc.Y << ")" << endl;
					actionList.splice(actionList.end(), actionList2);
				//	cout << "Moving on" << endl;
				}
				else {
					//no safe location left, lets go home, and stop ourselves from getting stuck.
				//	cout << "No Safe Route going home" << endl;
					actionList2 = searchEngine.FindPath(myState.agentLocation, myState.agentOrientation, Location(1, 1), RIGHT);
					actionList.splice(actionList.end(), actionList2);
					actionList.push_back(CLIMB);
				}
			}



		}
		//version 2, lets update location at this spot too



		Action action = actionList.front();
		if (action == GOFORWARD) {
			if (myState.agentOrientation == UP) {
				myState.agentLocation.Y += 1;
			}
			else if (myState.agentOrientation == DOWN) {
				myState.agentLocation.Y -= 1;
			}
			else if (myState.agentOrientation == LEFT) {
				myState.agentLocation.X -= 1;
			}
			else if (myState.agentOrientation == RIGHT) {
				myState.agentLocation.X += 1;
			}
		}
		else if (action == TURNLEFT) {
			if (myState.agentOrientation == UP) {
				myState.agentOrientation = LEFT;
			}
			else if (myState.agentOrientation == DOWN) {
				myState.agentOrientation = RIGHT;
			}
			else if (myState.agentOrientation == LEFT) {
				myState.agentOrientation = DOWN;
			}
			else if (myState.agentOrientation == RIGHT) {
				myState.agentOrientation = UP;
			}
		}
		else if (action == TURNRIGHT) {
			if (myState.agentOrientation == UP) {
				myState.agentOrientation = RIGHT;
			}
			else if (myState.agentOrientation == DOWN) {
				myState.agentOrientation = LEFT;
			}
			else if (myState.agentOrientation == LEFT) {
				myState.agentOrientation = UP;
			}
			else if (myState.agentOrientation == RIGHT) {
				myState.agentOrientation = DOWN;
			}

		}
		
		//cout << "Action and Orientation" << endl;
		//PrintAction(action);
		//cout << endl;
		//PrintOrientation(myState.agentOrientation);
		//cout << endl;

		if (actionList.empty() == false) {
			actionList.pop_front();
		}
		//cout << "Ending Cycle" << endl << "Location: " << myState.agentLocation.X << "," << myState.agentLocation.Y << endl;
		return action;
	/*}
	else {
	cin >> debug_counter;
}*/
}

void Agent::GameOver (int score)
{

}



//////////////////////////////////This works fine from the original as far as I can tell

bool Agent::findWumpus(list<Location> stench) {

	Location stench1, stench2;//dont need more than 2 locations
	int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0; // i dont see a reason to need more than 2 locations
	int tempX1 = 0, tempY1 = 0, tempX2 = 0, tempY2 = 0; //this way i can keep track of possible adjacent spots
	Location temp1, temp2; //this way i can pass them into the adjacent check and check if i've been there

	int wumpX = 0, wumpY = 0;//this is to store the wumpus location
	Location wumpSpot;
	cout << "Hunting for Wumpus" << endl;
	if (stench.empty()) {
		//if the list is empty, we don't know any locations
		cout << "No scent" << endl;
		return false;
	}
	else if (stench.size() == 1) {//only 1 known location, no way to check for location
		cout << "1 scent" << endl;
		return false;
	}
	//now with 2 or more we should be able to locate the wumpus using safe spots
	else {
		cout << "2 scent" << endl;
		//first, store the locations into easy to access spots
		stench1 = stench.front();
		stench2 = stench.back();
		X1 = stench1.X;
		Y1 = stench1.Y;
		X2 = stench2.X;
		Y2 = stench2.Y;


		//lets start with the 2 easiest variations, a line where x or y are the same
		if (X1 == X2) {//this is a verticle line, the y vars are different, and the wumpus is in between
			wumpX = X1;
			wumpY = (Y1 + Y2) / 2;
			wumpSpot.X = wumpX;
			wumpSpot.Y = wumpY;
		}
		else if (Y1 == Y2) {//Horizontal Line
			wumpX = Y1;
			wumpY = (X1 + X2) / 2;
			wumpSpot.X = wumpX;
			wumpSpot.Y = wumpY;
		}
		else {//okay so the two spots are diagonal to each other
			//so lets make 2 locations that combine coordinates to get the two spots
			tempX1 = X1;
			tempY1 = Y2;

			tempX2 = X2;
			tempY2 = Y1;

			temp1.X = tempX1;
			temp1.Y = tempY1;

			temp2.X = tempX2;
			temp2.Y = tempY2;

			//now lets iterate through the list, and see if we have been to one of these locations, if we have, we know its the other location
			//if we haven't, then check the other location see if we've been there, if we have, then the wumpus is in spot 2
			//if we haven't been to either, we can't know, so return false

			list<Location>::iterator it;
			int match = 0;
			for (it = visLoc.begin(); it != visLoc.end(); it++) {
				//check if it matches temp1
				if ((it->X == temp1.X) && (it->Y == temp1.Y)) {//it didnt like it==temp1, so broke it into smaller parts
					match = 1;
					break;//no need to go through the full list of visited spots
				}
			}
			//at this point, match=1 if we've been to temp1

			if (match != 1) {//match wasnt found, check temp2
				for (it = visLoc.begin(); it != visLoc.end(); it++) {
					if ((it->X == temp2.X) && (it->Y == temp2.Y)) {
						match = 2;
						break;//no need to go through the full list of visited spots
					}
				}

			}
			//match=2 if temp2, match=1 if temp1
			if (match == 1) {//spot 1 is safe, wumpus is spot 2
				wumpSpot = temp2;
				myState.wumpusLocation = wumpSpot;//store this for later
				searchEngine.RemoveSafeLocation(wumpSpot.X, wumpSpot.Y);
				//lets make the 4 spots around the wumpus safe for travel

				Location wumpU;//up
				Location wumpD;//down
				Location wumpR;//right
				Location wumpL;//left

				if (wumpSpot.Y + 1 <= myState.worldSize) {//we arent going out of bounds
					wumpU.X = wumpSpot.X;
					wumpU.Y = wumpSpot.Y + 1;
					//wumpU now matches the spot above the wumpus, add it to bot hsafe lists
					safeLoc.push_back(wumpU);
					searchEngine.AddSafeLocation(wumpU.X, wumpU.Y);
				}
				//repeat for the 3 other directions
				if (wumpSpot.Y - 1 >= 1) {
					wumpD.X = wumpSpot.X;
					wumpD.Y = wumpSpot.Y - 1;
					safeLoc.push_back(wumpD);
					searchEngine.AddSafeLocation(wumpD.X, wumpD.Y);
				}
				if (wumpSpot.X + 1 <= myState.worldSize) {
					wumpR.X = wumpSpot.X + 1;
					wumpR.Y = wumpSpot.Y;
					safeLoc.push_back(wumpR);
					searchEngine.AddSafeLocation(wumpR.X, wumpR.Y);
				}
				if (wumpSpot.X - 1 >= 1) {
					wumpL.X = wumpSpot.X - 1;
					wumpL.Y = wumpSpot.Y;
					safeLoc.push_back(wumpL);
					searchEngine.AddSafeLocation(wumpL.X, wumpL.Y);
				}
				cout << "Wumpus Found" << endl;
				return true;//all done, now we don't need to go through this any more
			}


			else if (match == 2) {//spot 2 is safe, wumpus is spot 1
			//literally the same as above, just pointing wumpSpot to the other spot

				wumpSpot = temp1;
				myState.wumpusLocation = wumpSpot;//store this for later
				searchEngine.RemoveSafeLocation(wumpSpot.X, wumpSpot.Y);
				//lets make the 4 spots around the wumpus safe for travel

				Location wumpU;//up
				Location wumpD;//down
				Location wumpR;//right
				Location wumpL;//left

				if (wumpSpot.Y + 1 <= myState.worldSize) {//we arent going out of bounds
					wumpU.X = wumpSpot.X;
					wumpU.Y = wumpSpot.Y + 1;
					//wumpU now matches the spot above the wumpus, add it to bot hsafe lists
					safeLoc.push_back(wumpU);
					searchEngine.AddSafeLocation(wumpU.X, wumpU.Y);
				}
				//repeat for the 3 other directions
				if (wumpSpot.Y - 1 >= 1) {
					wumpD.X = wumpSpot.X;
					wumpD.Y = wumpSpot.Y - 1;
					safeLoc.push_back(wumpD);
					searchEngine.AddSafeLocation(wumpD.X, wumpD.Y);
				}
				if (wumpSpot.X + 1 <= myState.worldSize) {
					wumpR.X = wumpSpot.X + 1;
					wumpR.Y = wumpSpot.Y;
					safeLoc.push_back(wumpR);
					searchEngine.AddSafeLocation(wumpR.X, wumpR.Y);
				}
				if (wumpSpot.X - 1 >= 1) {
					wumpL.X = wumpSpot.X - 1;
					wumpL.Y = wumpSpot.Y;
					safeLoc.push_back(wumpL);
					searchEngine.AddSafeLocation(wumpL.X, wumpL.Y);
				}
				cout << "Wumpus Found" << endl;
				return true;//all done, now we don't need to go through this any more


			}
			else {//neither
				cout << "Wumpus not Found" << endl;
				return false;
			}
		}

	}

}





bool Agent::safeSqaure() {//this is intended to solve the pit 3,1 wumpus 1,3 problem for all similar variations
	//THIS IS A VERY INTENSIVE FUNCTION, HOPEFULLY IT WONT BE NEEDED BUT IT PROBABLY WILL
	if (stenchSpot.empty() == true || breezeSpot.empty() == true) {//dont bother checking if either are empty
		return false;
	}
	//lets start by iterating through the stench spots, and then checking to make sure they're not also breeze spots
	//and vice versa
	//store these into a seperate list
	//go through list and check against other values for diagonal
	//if theyre diagonal then go through the process of adding their adjacent spots to the safe list
	list<Location> soloSpotBreeze;
	list<Location> soloSpotStench;

	list<Location>::iterator it1;
	list<Location>::iterator it2;
	int match = 0;
	for (it1 = stenchSpot.begin(); it1 != stenchSpot.end(); it1++) {
		//no easy way to check a location for its percepts, so have to step through breeze spots and compare against it
		for (it2 = breezeSpot.begin(); it2 != breezeSpot.end(); it2++) {
			if ((it1->X == it2->X) && (it1->Y == it2->Y)) {//if the coordinates match
				match = 1;//a match has been found
			}
		}
		if (match == 0) {//no match found, add this location to the solo list
			soloSpotStench.push_back(Location(it1->X, it1->Y));
		}
	}
	//repeat but for breeze
	match = 0;
	for (it1 = breezeSpot.begin(); it1 != breezeSpot.end(); it1++) {
		//no easy way to check a location for its percepts, so have to step through breeze spots and compare against it
		for (it2 = stenchSpot.begin(); it2 != stenchSpot.end(); it2++) {
			if ((it1->X == it2->X) && (it1->Y == it2->Y)) {//if the coordinates match
				match = 1;//a match has been found
			}
		}
		if (match == 0) {//no match found, add this location to the solo list
			soloSpotBreeze.push_back(Location(it1->X, it1->Y));
		}
	}

	//okay at this point we should have all the solo locations
	//lets check for diagonal spots and do the safeloc stuff

	//this should only require one iteration through luckily
	Location diag1; //Upper left
	Location diag2;//upper right
	Location diag3;//bottom left
	Location diag4;//bottom right
	for (it1 = soloSpotStench.begin(); it1 != soloSpotStench.end(); it1++) {
		//lets set the 4 locations around it and check them against the breeze
		/*diag1.X = it1->X - 1;
		diag1.Y = it1->Y + 1;
		diag2.X = it1->X + 1;
		diag2.Y = it1->Y + 1;
		diag3.X = it1->X - 1;
		diag3.Y = it1->Y - 1;
		diag4.X = it1->X + 1;
		diag4.Y = it1->Y - 1;*/


		for (it2 = soloSpotBreeze.begin(); it2 != soloSpotBreeze.end(); it2++) {
		//check if any of the breeze spots match a diagonal

			//if ((it2->X == diag1.X) && (it2->Y == diag1.Y)) {

			//}
			//else if ((it2->X == diag2.X) && (it2->Y == diag2.Y)) {
			//}
			//else if ((it2->X == diag3.X) && (it2->Y == diag3.Y)) {
			//}
			//else if ((it2->X == diag4.X) && (it2->Y == diag4.Y)) {
			//	int X1 = it1->X;
			//	int Y1 = it1->Y;
			//	int X2 = it2->X;
			//	int Y2 = it2->Y;
			//	Location spot1 = Location(X1, Y2);
			//	Location spot2 = Location(X2, Y1);

			//	list<Location>::iterator it3;
			//	for (it3 = visLoc.begin(); it3 != visLoc.end(); it3++) {
			//		if ((it3->X == spot1.X) && (it3->Y == spot1.Y)) {
			//		//add spot 2 to safeLoc
			//			searchEngine.AddSafeLocation(spot2.X, spot2.Y);
			//			safeLoc.push_back(spot2);
			//		}
			//		else if ((it3->X == spot2.X) && (it3->Y == spot2.Y)) {
			//		//add spot 1 to safe loc
			//			searchEngine.AddSafeLocation(spot1.X, spot1.Y);
			//			safeLoc.push_back(spot1);
			//		}
			//	}

			//}
			int X1 = it1->X;
				int Y1 = it1->Y;
				int X2 = it2->X;
				int Y2 = it2->Y;
				Location spot1 = Location(X1, Y2);
				Location spot2 = Location(X2, Y1);

				list<Location>::iterator it3;
				for (it3 = visLoc.begin(); it3 != visLoc.end(); it3++) {
					if ((it3->X == spot1.X) && (it3->Y == spot1.Y)) {
						//add spot 2 to safeLoc
						searchEngine.AddSafeLocation(spot2.X, spot2.Y);
						safeLoc.push_back(spot2);
					}
					else if ((it3->X == spot2.X) && (it3->Y == spot2.Y)) {
						//add spot 1 to safe loc
						searchEngine.AddSafeLocation(spot1.X, spot1.Y);
						safeLoc.push_back(spot1);
					}
				}

		}
	}

}
