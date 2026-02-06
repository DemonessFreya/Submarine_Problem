#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
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

bool is_valid_degree(int degree);
int closest_submarine(int degree, vector<int> subLocations);
int distance_calc(int degree, int playerDegree);
void enemy_distance();

int main() {
	enemy_distance();

	std::cout << "Please enter an angle between 0-360 degrees" << std::endl;
	do { std::cin >> inputDegree; } while (is_valid_degree(inputDegree)); // ask valid degree until given

	playerDegree = inputDegree;

	enemy_distance();

	return 0;
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

	for (int i : subLocations) {
		if (degree - i >= difference) {
			enemyDegree = i;
		}
		difference = degree - i;
	}

	return enemyDegree;
}

// calculate how far the player guess was
int distance_calc(int degree, int playerDegree) {
	degree = degree - playerDegree;

	return degree;
}

// display enemy distance to player
void enemy_distance() {
	int enemyDegree = closest_submarine(playerDegree, subLocations);
	int distance = distance_calc(enemyDegree, playerDegree);

	if (distance < 0) {
		std::cout << "Enemy " << abs(distance) << " degrees to the left" << std::endl;
	}
	else if (distance > 0) {
		std::cout << "Enemy " << distance << " degrees to the right" << std::endl;
	}
	else {
		std::cout << "How?" << std::endl;
	}
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