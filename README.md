# The Game
It is the year 2442...
...the world has been ravaged by a combination of climate change and natural disasters. In San Francisco, California, a number of surviving humans have formed clans inside heat-proof bunkers to protect themselves from the deadly rays of a now harmful sun.

These survivors still need access to earth's most precious natural resource: water. Advances in robotics make it possible to send out a drone into the desert in search of water. However, due to a limited stock of ressource, only one drone will be selected to do this and it must be as efficient as possible. The best programmers in the clan have written AIs but which one will be able to safely navigate the desert in the shortest possible time ?

A race is thus organized to determine which AI will be used for this most vital of missions.

Write your code, and become the acclaimed savior of your clan.

## The Goal
Win the race.

## Rules
* The game is played on a map 16000 units wide and 9000 units high.
* The coordinate X=0, Y=0 is the top left pixel.
* The players each control a drone and compete in a race. There may be two or three racers at once.
* The circuit of the race is made up of checkpoints. To complete one lap, your drone must pass through each one in order and back through the start. The first player to reach the start on the final lap wins.

### The checkpoints work as follows:

* The checkpoints are circular, with a radius of 600 units.
* Checkpoints are numbered from 0 to N where 0 is the start and N-1 is the last checkpoint.
* The disposition of the checkpoints is selected randomly for each race.

### The drones work as follows:

* The drones have a circular shield around their center, with a radius of 400 units.
* To pass a checkpoint, the center of a drone must be inside the radius of the checkpoint.
* To move a drone, you must print a target destination point followed by a thrust value. Details of the protocol can be found further down.
* The thrust value of a drone must be between 0 and 100.
* You may use the keyword BOOST instead of the thrust value to give your drone a short acceleration boost. You may only do a given amount of times per game. If you have already consumed your boost and still print BOOST, the thrust will default to 100.
* If your drone does not make it to the next checkpoint in under 100 turns, you are eliminated and can no longer control your drone.
* The drones may move normally outside the game area.

    Note: You may activate debug mode in the settings panel () to view additional game data.

## Victory Conditions
* Be the first to complete all the laps of the circuit.

## Lose Conditions
* Your program provides incorrect output.
* Your program times outs.
* Your drone does not reach the next checkpoint in time.
* Somebody else wins.

## Expert Rules

### On each turn the drones movements are computed this way:
* Thrust: the normalized vector between the position of the drone and its target is multiplied by the given thrust value. The result is added to the current speed vector.
* Movement: The speed vector is added to the position of the pod. If a collision would occur at this point, the pods rebound off each other.
* Friction: the current speed vector of each drone is multiplied by 0.85

    The speed's values are truncated and the position's values are rounded to the nearest integer.

### Note
The program must first read the initialization data from standard input. Then, within an infinite loop, read the contextual data from the standard input (player positions and state of the grid) and provide to the standard output the desired instructions.

## Game Input

### Initialization input
* Line 1: playerCount: the number of drones in the race.
* Line 2: laps: the number of laps to complete the race.
* Line 3: boosts, the number of boosts you can use during the race.
* Line 4: checkpointCount: the number of checkpoints in the circuit.
* Next checkpointCount lines: 2 integerscheckpointX, checkpointY for the coordinates of the checkpoint.

### Input for one game turn
* Next playerCount lines: 5 integers representing one of the drones. The first drone of the list is always yours. x & y for the position. vx & vy for the speed vector. nextCheckPointId for the number of the next checkpoint the drone must go through.

### Output for one game turn
* A single line: 2 integers for the target coordinates of your drone followed by thrust, the acceleration to give your drone or the keyword BOOST.

##Constraints
* 0 <= thrust <= 100
* 2 <= playerCount <= 3
* 2 <= checkpointCount <= 8
* 2 <= boosts <= 8
* Response time per turn <= 100ms

