// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
     Species food('f');
     Action f_a1(LEFT);
     Control f_c2(GO, 0);
     assert(food.addInstruction(f_a1) == 1);
     assert(food.addInstruction(f_c2) == 2);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

     Species hopper('h');
     Action h_a1(HOP);
     Control h_c2(GO, 0);
     assert(hopper.addInstruction(h_a1) == 1);
     assert(hopper.addInstruction(h_c2) == 2);

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

     Species rover('r');
     Control r_c1(IF_ENEMY, 9);
     Control r_c2(IF_EMPTY, 7);
     Control r_c3(IF_RANDOM, 5);
     Action r_a4(LEFT);
     Control r_c5(GO, 0);
     Action r_a6(RIGHT);
     Control r_c7(GO, 0);
     Action r_a8(HOP);
     Control r_c9(GO, 0);
     Action r_a10(INFECT);
     Control r_c11(GO, 0);

     assert(rover.addInstruction(r_c1) == 1);
     assert(rover.addInstruction(r_c2) == 2);
     assert(rover.addInstruction(r_c3) == 3);
     assert(rover.addInstruction(r_a4) == 4);
     assert(rover.addInstruction(r_c5) == 5);
     assert(rover.addInstruction(r_a6) == 6);
     assert(rover.addInstruction(r_c7) == 7);
     assert(rover.addInstruction(r_a8) == 8);
     assert(rover.addInstruction(r_c9) == 9);
     assert(rover.addInstruction(r_a10) == 10);
     assert(rover.addInstruction(r_c11) == 11);

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */


     Species trap('t');
     Control t_c1(IF_ENEMY,3);
     Action t_a2(LEFT);
     Control t_c3(GO,0);
     Action t_a4(INFECT);
     Control t_c5(GO, 0);

     assert(trap.addInstruction(t_c1) == 1);
     assert(trap.addInstruction(t_a2) == 2);
     assert(trap.addInstruction(t_c3) == 3);
     assert(trap.addInstruction(t_a4) == 4);
     assert(trap.addInstruction(t_c5) == 5);

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */

    Creature c1(food, EAST, 0);
    Creature c2(hopper, NORTH, 0);
    Creature c3(hopper, EAST, 0);
    Creature c4(hopper, SOUTH, 0);
    Creature c5(hopper, WEST, 0);
    Creature c6(food, NORTH, 0);

    Darwin grid1(8,8);
    grid1.addCreature(c1,0,0);
    grid1.addCreature(c2,3,3);
    grid1.addCreature(c3,3,4);
    grid1.addCreature(c4,4,4);
    grid1.addCreature(c5,4,3);
    grid1.addCreature(c6,7,7);

    grid1.display();

    // *** DESTROY *** //
    //grid1.~Darwin();
    //c1.~Creature();

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */

    Creature d1(trap, SOUTH, 0);
    Creature d2(hopper, EAST, 0);
    Creature d3(rover, NORTH, 0);
    Creature d4(trap, WEST, 0);

    Darwin grid2(7,9);
    grid2.addCreature(d1,0,0);
    grid2.addCreature(d2,3,2);
    grid2.addCreature(d3,5,4);
    grid2.addCreature(d4,6,8);

    grid2.display();
    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;}
