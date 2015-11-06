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
     assert(food.addInstruction(Instruction(LEFT)) == 1);
     assert(food.addInstruction(Instruction(GO,0)) == 2);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

     Species hopper('h');
     assert(hopper.addInstruction(Instruction(HOP)) == 1);
     assert(hopper.addInstruction(Instruction(GO,0)) == 2);

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
     assert(rover.addInstruction(Instruction(IF_ENEMY, 9)) == 1);
     assert(rover.addInstruction(Instruction(IF_EMPTY, 7)) == 2);
     assert(rover.addInstruction(Instruction(IF_RANDOM, 5)) == 3);
     assert(rover.addInstruction(Instruction(LEFT)) == 4);
     assert(rover.addInstruction(Instruction(GO,0)) == 5);
     assert(rover.addInstruction(Instruction(RIGHT)) == 6);
     assert(rover.addInstruction(Instruction(GO,0)) == 7);
     assert(rover.addInstruction(Instruction(HOP)) == 8);
     assert(rover.addInstruction(Instruction(GO,0)) == 9);
     assert(rover.addInstruction(Instruction(INFECT)) == 10);
     assert(rover.addInstruction(Instruction(GO,0)) == 11);

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
     assert(trap.addInstruction(Instruction(IF_ENEMY,3)) == 1);
     assert(trap.addInstruction(Instruction(LEFT)) == 2);
     assert(trap.addInstruction(Instruction(GO,0)) == 3);
     assert(trap.addInstruction(Instruction(INFECT)) == 4);
     assert(trap.addInstruction(Instruction(GO,0)) == 5);

    // ----
    // best
    // ----

     Species best1('b');
     assert(best1.addInstruction(Instruction(IF_ENEMY, 9)) == 1);
     assert(best1.addInstruction(Instruction(IF_EMPTY, 7)) == 2);
     assert(best1.addInstruction(Instruction(IF_RANDOM, 5)) == 3);
     assert(best1.addInstruction(Instruction(LEFT)) == 4);
     assert(best1.addInstruction(Instruction(GO,0)) == 5);
     assert(best1.addInstruction(Instruction(RIGHT)) == 6);
     assert(best1.addInstruction(Instruction(GO,0)) == 7);
     assert(best1.addInstruction(Instruction(HOP)) == 8);
     assert(best1.addInstruction(Instruction(GO,0)) == 9);
     assert(best1.addInstruction(Instruction(INFECT)) == 10);
     assert(best1.addInstruction(Instruction(LEFT)) == 11);
     assert(best1.addInstruction(Instruction(GO,0)) == 12);

     Species best('b');
     assert(best.addInstruction(Instruction(IF_ENEMY, 6)) == 1);
     assert(best.addInstruction(Instruction(IF_EMPTY, 4)) == 2);
     assert(best.addInstruction(Instruction(LEFT)) == 3);
     assert(best.addInstruction(Instruction(GO,0)) == 4);
     assert(best.addInstruction(Instruction(HOP)) == 5);     
     assert(best.addInstruction(Instruction(GO,0)) == 6);
     assert(best.addInstruction(Instruction(INFECT)) == 7);     
     assert(best.addInstruction(Instruction(GO,0)) == 8);

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

    Creature c1(food, EAST);
    Creature c2(hopper, NORTH);
    Creature c3(hopper, EAST);
    Creature c4(hopper, SOUTH);
    Creature c5(hopper, WEST);
    Creature c6(food, NORTH);

    Darwin grid1(8,8);
    grid1.addCreature(c1,0,0);
    grid1.addCreature(c2,3,3);
    grid1.addCreature(c3,3,4);
    grid1.addCreature(c4,4,4);
    grid1.addCreature(c5,4,3);
    grid1.addCreature(c6,7,7);

    grid1.simulate(5,cout);

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

    Creature d1(trap, SOUTH);
    Creature d2(hopper, EAST);
    Creature d3(rover, NORTH);
    Creature d4(trap, WEST);

    Darwin grid2(7,9);
    grid2.addCreature(d1,0,0);
    grid2.addCreature(d2,3,2);
    grid2.addCreature(d3,5,4);
    grid2.addCreature(d4,6,8);

    grid2.simulate(5,cout);

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

    Darwin grid_without_best(72,72);

    // Create food species/creature
    for (int i = 0; i < 10; i++){
        int pos = rand() % 5184;
        DIRECTION direction =  static_cast<DIRECTION>(rand() % 4);
        Creature b1(food, direction);
        grid_without_best.addCreature(b1, pos);      
    }

    //Create hopper species/creature
    for (int i = 0; i < 10; i++){
        int pos = rand() % 5184;
        DIRECTION direction =  static_cast<DIRECTION>(rand() % 4);
        Creature b1(hopper, direction);
        grid_without_best.addCreature(b1, pos);      
    }

    // Create rover species/creature
    for (int i = 0; i < 10; i++){
        int pos = rand() % 5184;
        DIRECTION direction =  static_cast<DIRECTION>(rand() % 4);
        Creature b1(rover, direction);
        grid_without_best.addCreature(b1, pos);      
    }

    // Create trap species/creature
    for (int i = 0; i < 10; i++){
        int pos = rand() % 5184;
        DIRECTION direction =  static_cast<DIRECTION>(rand() % 4);
        Creature b1(trap, direction);
        grid_without_best.addCreature(b1, pos);      
    }

    grid_without_best.simulate(1000,cout);    
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

    Darwin grid_with_best(72,72);

    // Create food species/creature
    for (int i = 0; i < 10; i++){
        int pos = rand() % 5184;
        DIRECTION direction =  static_cast<DIRECTION>(rand() % 4);
        Creature b1(food, direction);
        grid_with_best.addCreature(b1, pos);      
    }

    //Create hopper species/creature
    for (int i = 0; i < 10; i++){
        int pos = rand() % 5184;
        DIRECTION direction =  static_cast<DIRECTION>(rand() % 4);
        Creature b1(hopper, direction);
        grid_with_best.addCreature(b1, pos);      
    }

    // Create rover species/creature
    for (int i = 0; i < 10; i++){
        int pos = rand() % 5184;
        DIRECTION direction =  static_cast<DIRECTION>(rand() % 4);
        Creature b1(rover, direction);
        grid_with_best.addCreature(b1, pos);      
    }

    // Create trap species/creature
    for (int i = 0; i < 10; i++){
        int pos = rand() % 5184;
        DIRECTION direction =  static_cast<DIRECTION>(rand() % 4);
        Creature b1(trap, direction);
        grid_with_best.addCreature(b1, pos);      
    }

    // Create trap species/creature
    for (int i = 0; i < 10; i++){
        int pos = rand() % 5184;
        DIRECTION direction =  static_cast<DIRECTION>(rand() % 4);
        Creature b1(best1, direction);
        grid_with_best.addCreature(b1, pos);      
    }

    grid_with_best.simulate(1000,cout);    
    return 0;}
