#include <iostream>

/**
Statement:
Johnny and Roy do not go to class; they prefer to play wars of ships. As now they want to play it in a computer, they have asked Steffy to write them a program. Unfortunately, Steffy is studying NP-complete problems, so she has passed you the order.

According to Johnny and Roy rules, the game is played in a rectangular grid. First, Johnny sets the ships in the grid (obviously, Roy can not see where Johnny sets the ships). After that, Roy shoots, trying to sink the ships. When in the coordinate that Roy says there is not any ship, Johnny says “water’’. When a ship is hit but it is not sunk, Johnny says “hit’’. If with this shoot all the positions of the ship have been hit, Johnny says “sunk’’, but in the future he will say “water’’ for any of these positions.

Your task is to write a program that reads a grid of ships and a sequence of shoots. For each shoot, the program must print “water”, “hit” or “sunk” as explained in the rules. Moreover, the program has to print the final state of the fleet.

Input

The number of rows f and the number of columns c of the grid are given first; 3 ≤ f ≤ 26 and c ≥ 3 are fulfilled. After that, there are f lines with c characters each one. A dot indicates an empty position, a ‘|S|’ a ship position. Ships are placed horizontally, and they can not touch themselves nor the border of the grid. Finally, a non empty sequence of shoots is given (all of them inside the grid), indicating the row with a lowercase letter and the column with a natural number. The position on the top and left is a |0|.

Output

Your program must print each shoot followed by its result (“water”, “hit” or “sunk”) as it is shown in the instances. After that, the program must print an empty line and then print the state of the grid. Print a character ‘|T|’ for the positions which are hit but not sink.


*/

using namespace std;

int main() {
	return 0;
}


