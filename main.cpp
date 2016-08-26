#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int playerCount; // number of drones in the race. You are always the first drone in the list.
    cin >> playerCount; cin.ignore();
    int laps; // number of laps
    cin >> laps; cin.ignore();
    int boosts; // number of boosts you can use for this race
    cin >> boosts; cin.ignore();
    int checkpointCount; // number of checkpoints for one lap
    cin >> checkpointCount; cin.ignore();
    for (int i = 0; i < checkpointCount; i++) {
        int checkpointX;
        int checkpointY;
        cin >> checkpointX >> checkpointY; cin.ignore();
    }

    // game loop
    while (1) {
        for (int i = 0; i < playerCount; i++) {
            int x;
            int y;
            int vx;
            int vy;
            int nextCheckPointId;
            cin >> x >> y >> vx >> vy >> nextCheckPointId; cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // Coordinates of target point X Y, followed by the thrust to feed to the engines (0 to 100 or BOOST).
        cout << "8000 4500 100" << endl;
    }
}
