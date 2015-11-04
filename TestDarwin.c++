#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <typeinfo>
#include "gtest/gtest.h"
#include "Darwin.h"

using namespace std;

TEST(Species, species_1) {
	Species s('h');
	ASSERT_EQ(s.addInstruction(Instruction(HOP)), 1);
	ASSERT_EQ(s.addInstruction(Instruction(HOP)), 2);
	ASSERT_EQ(s.addInstruction(Instruction(LEFT)), 3);
	ASSERT_EQ(s.addInstruction(Instruction(GO,0)), 4);
	ASSERT_EQ(s._name,'h');
}

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */


/* INFECT WEST */
TEST(Action_Instructions, infect_1){

	Species hopper('h');
    assert(hopper.addInstruction(Instruction(HOP)) == 1);
    assert(hopper.addInstruction(Instruction(GO,0)) == 2);

	Species rover('r');
	assert(rover.addInstruction(Instruction(IF_ENEMY, 2)) == 1);
	assert(rover.addInstruction(Instruction(IF_EMPTY, 4)) == 2);
	assert(rover.addInstruction(Instruction(INFECT)) == 3);
	assert(rover.addInstruction(Instruction(HOP)) == 4);
	assert(rover.addInstruction(Instruction(GO,0)) == 5);

	Creature c1(hopper, EAST);
	Creature c2(rover, WEST);

	Darwin grid1(3,3);

	grid1.addCreature(c1,1,0);
	grid1.addCreature(c2,1,2);

	// * * *
	// h * r
	// * * *

	ostringstream w;
	grid1.simulate(1,w);
	ASSERT_EQ(w.str(),"Turn = 0.\n 012\n0...\n1h.r\n2...\n\nTurn = 1.\n 012\n0...\n1.rr\n2...\n\n");
}

// /* INFECT EAST */
// TEST(Action_Instructions, infect_2){

// 	Species hopper('h');
//     assert(hopper.addInstruction(Instruction(HOP)) == 1);
//     assert(hopper.addInstruction(Instruction(GO,0)) == 2);

// 	Species rover('r');
// 	assert(rover.addInstruction(Instruction(IF_ENEMY, 2)) == 1);
// 	assert(rover.addInstruction(Instruction(IF_EMPTY, 4)) == 2);
// 	assert(rover.addInstruction(Instruction(INFECT)) == 3);
// 	assert(rover.addInstruction(Instruction(HOP)) == 4);
// 	assert(rover.addInstruction(Instruction(GO,0)) == 5);

// 	Creature c1(hopper, SOUTH);
// 	Creature c2(rover, EAST);

// 	Darwin grid1(4,3);

// 	grid1.addCreature(c1,0,1);
// 	grid1.addCreature(c2,1,0);

// 	// * h *
// 	// r * *
// 	// * * *
// 	// * * *

// 	grid1.simulate(1);
// 	//ASSERT_EQ(grid1.simulate(1)," 012\n0...\n1h.r\n2...\n");

// }

//  INFECT SOUTH 
// TEST(Action_Instructions, infect_3){

// 	Species hopper('h');
//     assert(hopper.addInstruction(Instruction(HOP)) == 1);
//     assert(hopper.addInstruction(Instruction(GO,0)) == 2);

// 	Species rover('r');
// 	assert(rover.addInstruction(Instruction(IF_ENEMY, 2)) == 1);
// 	assert(rover.addInstruction(Instruction(IF_EMPTY, 4)) == 2);
// 	assert(rover.addInstruction(Instruction(INFECT)) == 3);
// 	assert(rover.addInstruction(Instruction(HOP)) == 4);
// 	assert(rover.addInstruction(Instruction(GO,0)) == 5);

// 	Creature c1(hopper, EAST);
// 	Creature c2(rover, SOUTH);

// 	Darwin grid1(3,4);

// 	grid1.addCreature(c1,2,1);
// 	grid1.addCreature(c2,0,3);

// 	// * * * r
// 	// * * * *
// 	// * h * *


// 	// grid1.display();
// 	// grid1.simulate(1);
// 	//ASSERT_EQ(grid1.simulate(1)," 012\n0...\n1h.r\n2...\n");

// }

// /* INFECT NORTH */
// TEST(Action_Instructions, infect_3){

//      Species food('f');
//      assert(food.addInstruction(Instruction(LEFT)) == 1);
//      assert(food.addInstruction(Instruction(GO,0)) == 2);

// 	Species rover('r');
// 	assert(rover.addInstruction(Instruction(IF_ENEMY, 2)) == 1);
// 	assert(rover.addInstruction(Instruction(IF_EMPTY, 4)) == 2);
// 	assert(rover.addInstruction(Instruction(INFECT)) == 3);
// 	assert(rover.addInstruction(Instruction(HOP)) == 4);
// 	assert(rover.addInstruction(Instruction(GO,0)) == 5);

// 	Creature c1(food, WEST);
// 	Creature c2(rover, NORTH);

// 	Darwin grid1(2,2);

// 	grid1.addCreature(c1,0,1);
// 	grid1.addCreature(c2,1,1);

// 	// * f
// 	// * r

// 	// grid1.display();
// 	// grid1.simulate(1);
// 	//ASSERT_EQ(grid1.simulate(1)," 012\n0...\n1h.r\n2...\n");

// }

// TEST(Action_Instructions, hop_1) {
// 	Species hopper('h');
// 	hopper.addInstruction(Instruction(HOP));
//     hopper.addInstruction(Instruction(GO,0));

//     Creature c1(hopper, NORTH);

//     Darwin grid(3,3);
//     grid.addCreature(c1, 2, 2);

//     ostringstream w;
// 	grid1.simulate(1,w);
// 	ASSERT_EQ(w.str(),"Turn = 0.\n 
// 		012\n
// 	   0...\n
// 	   1.h.\n
// 	   2...\n");
// }

/**
 * Tests the left() function when facing NORTH
 */
TEST(Action_Instructions, turn_left_1)
{
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, NORTH);
    d.left(c);

    ASSERT_EQ(c._direction, WEST);
}

/**
 * Tests the left() function when facing EAST
 */
TEST(Action_Instructions, turn_left_2)
{
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, EAST);
    d.left(c);

    ASSERT_EQ(c._direction, NORTH);
}

/**
 * Tests the left() function when facing SOUTH
 */
TEST(Action_Instructions, turn_left_3)
{
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, SOUTH);
    d.left(c);

    ASSERT_EQ(c._direction, EAST);
}

/**
 * Tests the left() function when facing WEST
 */
TEST(Action_Instructions, turn_left_4)
{
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, WEST);
    d.left(c);

    ASSERT_EQ(c._direction, SOUTH);
}

/**
 * Tests the right() function when facing NORTH
 */
TEST(Action_Instructions, turn_right_1)
{
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, NORTH);
    d.right(c);

    ASSERT_EQ(c._direction, EAST);
}

/**
 * Tests the right() function when facing EAST
 */
TEST(Action_Instructions, turn_right_2)
{
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, EAST);
    d.right(c);

    ASSERT_EQ(c._direction, SOUTH);
}

/**
 * Tests the right() function when facing SOUTH
 */
TEST(Action_Instructions, turn_right_3)
{
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, SOUTH);
    d.right(c);

    ASSERT_EQ(c._direction, WEST);
}

/**
 * Tests the right() function when facing WEST
 */
TEST(Action_Instructions, turn_right_4)
{
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, WEST);
    d.right(c);

    ASSERT_EQ(c._direction, NORTH);
}