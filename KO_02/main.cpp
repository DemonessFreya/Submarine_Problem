#include <iostream>
#include <vector>
using namespace std;

// enemy sub locations in degrees
vector<int> subLocations {
	60,
	120,
	40,
	210
};

int playerDegree = 0; // current position
int inputDegree = -1; // target position
int playerDistanceToEnemy = 0;

int player_input(int inputDegree);
bool is_valid_degree(int degree);
int closest_submarine(int degree, vector<int> subLocations);
int distance_calc(int degree, int playerDegree);
int enemy_distance();
void kill_enemy(vector<int>& subLocations, int inputDegree);
bool is_enemy_hit(int enemyLocation, int inputDegree);

int main() {
	while (!subLocations.empty()) {
		int enemyDistance = enemy_distance(); // show closest enemy location

		inputDegree = player_input(inputDegree); // player input

		playerDistanceToEnemy = enemyDistance;

		if (playerDistanceToEnemy / inputDegree == 1) {
			kill_enemy(subLocations, playerDistanceToEnemy); // kill enemy if hit
		}
	}

	return 0;
}

int player_input(int inputDegree) {
	cout << "Please enter an angle between 0-360 degrees" << endl;
	do { std::cin >> inputDegree; } while (is_valid_degree(inputDegree)); // ask valid degree until given

	return inputDegree;
}

// make sure player input fits within range 0-360
bool is_valid_degree(int degree) {
	bool degreeCheck = false;
	degreeCheck = ((degree >= 0) && (degree <= 360));
	if (!degreeCheck) cout << "Please enter valid number between 0-360." << endl; // only send when invalid degree

	return !degreeCheck; // return false to break loop
}

// find which enemy is closest to player
int closest_submarine(int degree, vector<int> subLocations) {
	int enemyDegree = 0;
	int difference = degree - subLocations[0];

	// iterate through each vector member and decide which is closer via a difference variable
	for (int location : subLocations) {
		if (degree - location >= difference) {
			enemyDegree = location;
		}
		difference = degree - location;
	}

	return enemyDegree;
}

// calculate how far the player guess was
int distance_calc(int degree, int playerDegree) {
	degree = degree - playerDegree;

	return degree;
}

// display enemy distance to player
int enemy_distance() {
	int enemyDegree = closest_submarine(playerDegree, subLocations);
	int enemyDistance = distance_calc(enemyDegree, playerDegree);

	if (enemyDistance < 0) {
		std::cout << "Enemy " << abs(enemyDistance) << " degrees to the left" << std::endl;
	}
	else if (enemyDistance > 0) {
		std::cout << "Enemy " << enemyDistance << " degrees to the right" << std::endl;
	}
	else {
		std::cout << "How?" << std::endl;
	}

	return enemyDistance;
}

void kill_enemy(vector<int>& subLocations, int inputDegree) {
	// iterate through each vector member and if it is in the location the player hit, erase it from the vector
	for (vector<int>::iterator iter = subLocations.begin(); iter != subLocations.end();) {
		if (is_enemy_hit(*iter, inputDegree)) {
			playerDegree = closest_submarine(playerDegree, subLocations); // place player at location of input target
			iter = subLocations.erase(iter);
			cout << "Enemy destroyed!" << endl;
		}
		else {
			++iter;
		}
	}
}

// check if enemy hit
bool is_enemy_hit(int enemyLocation, int inputDegree) {
	// need to find a way for this to work for every single member of the vector
	if ((inputDegree + enemyLocation) - playerDistanceToEnemy == playerDistanceToEnemy) {
		return true;
	}

	return false;
}

// --Submarine game--
//
// (level I - one enemy unit)
// 1 - Player enter the enemy location between 0 - 360 degree on radar screen.
// 2 - Submarine detect the minimum rotation and direction, then destroys the enemy and shows messages.
// > example: player entered 60 -- > result: Enemy unit detected at 60 degree!Turn "RIGHT" 60 degrees!
// > example: player entered 320 -- > result: Enemy unit detected at 320 degree!Turn "LEFT" 40 degrees!
// (level II - 4 enemy units)
// 1 - Player enters the enemy locations between 0 - 360 degree on radar screen for 4 enemy units.
// 2 - Submarine must destroy the closest one FIRST, and then the closet one to it NEXT, and then same for enemy 3 and 4.
// 
// (level III - 4 enemy units, one of them is priority target)
// 1 - Player enters 4 enemy locations, and assign one as priority target. (can be the first or last entry)
// 2 - The priority target MUST destroyed FIRST !
// 3 - Then  after destroying priority target, Submarine must destroy the closest one to it, and then the closet one to it as next, and then same for last.