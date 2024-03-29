/** @file TestDarwin.c++
 *  @brief This file contains unit tests to test the functions and methods
 *         contained in Darwin.c++.
 */

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <typeinfo>
#include "gtest/gtest.h"
#include "Darwin.h"

using namespace std;

// ------------
// Infect Tests
// ------------

/**
 * Tests the infect() function when facing WEST
 * @param Infect_Tests a fixture
 * @param infect_1 test name
 */
TEST(Infect_Tests, infect_1) {

	Species hopper('h');
    hopper.addInstruction(Instruction(HOP));
    hopper.addInstruction(Instruction(GO,0));

	Species rover('r');
	rover.addInstruction(Instruction(IF_ENEMY, 2));
	rover.addInstruction(Instruction(IF_EMPTY, 4));
	rover.addInstruction(Instruction(INFECT));
	rover.addInstruction(Instruction(HOP));
	rover.addInstruction(Instruction(GO,0));

	Creature c1(hopper, EAST);
	Creature c2(rover, WEST);

	Darwin grid1(3,3);

	grid1.addCreature(c1,1,0);
	grid1.addCreature(c2,1,2);

	ostringstream w;
	grid1.simulate(1,w);
	ASSERT_EQ(w.str(),"Turn = 0.\n 012\n0...\n1h.r\n2...\n\nTurn = 1.\n 012\n0...\n1.rr\n2...\n\n");
}

/**
 * Tests the infect() function when facing EAST
 * @param Infect_Tests a fixture
 * @param infect_2 test name
 */
TEST(Infect_Tests, infect_2){

	Species hopper('h');
    hopper.addInstruction(Instruction(HOP));
    hopper.addInstruction(Instruction(GO,0));

	Species rover('r');
	rover.addInstruction(Instruction(IF_ENEMY, 2));
	rover.addInstruction(Instruction(IF_EMPTY, 4));
	rover.addInstruction(Instruction(INFECT));
	rover.addInstruction(Instruction(HOP));
	rover.addInstruction(Instruction(GO,0));

	Creature c1(hopper, SOUTH);
	Creature c2(rover, EAST);

	Darwin grid1(4,3);

	grid1.addCreature(c1,0,1);
	grid1.addCreature(c2,1,0);

	ostringstream w;
	grid1.simulate(1,w);
	ASSERT_EQ(w.str(),"Turn = 0.\n 012\n0.h.\n1r..\n2...\n3...\n\nTurn = 1.\n 012\n0...\n1rr.\n2...\n3...\n\n");

}

/**
 * Tests the infect() function when facing NORTH
 * @param Infect_Tests a fixture
 * @param infect_3 test name
 */
TEST(Infect_Tests, infect_3){

    Species food('f');
    food.addInstruction(Instruction(LEFT));
    food.addInstruction(Instruction(GO,0));

	Species rover('r');
	rover.addInstruction(Instruction(IF_ENEMY, 2));
	rover.addInstruction(Instruction(IF_EMPTY, 4));
	rover.addInstruction(Instruction(INFECT));
	rover.addInstruction(Instruction(HOP));
	rover.addInstruction(Instruction(GO,0));

	Creature c1(food, WEST);
	Creature c2(rover, NORTH);

	Darwin grid1(2,2);

	grid1.addCreature(c1,0,1);
	grid1.addCreature(c2,1,1);

	ostringstream w;
	grid1.simulate(1,w);
	ASSERT_EQ(w.str(),"Turn = 0.\n 01\n0.f\n1.r\n\nTurn = 1.\n 01\n0.r\n1.r\n\n");

}

// -------------
// If Wall Tests
// -------------

/**
 * Tests if_wall() when facing WEST
 * @param Control_Instructions a fixture
 * @param if_wall_1 test name
 */
TEST(If_Wall_Tests, if_wall_1) {

	Species kahli('k');
	assert(kahli.addInstruction(Instruction(IF_WALL, 3)) == 1);
	assert(kahli.addInstruction(Instruction(HOP)) == 2);
	assert(kahli.addInstruction(Instruction(LEFT, 4)) == 3);
	assert(kahli.addInstruction(Instruction(GO,2)) == 4);

	Creature c1(kahli, WEST);

	Darwin grid1(4,3);

	grid1.addCreature(c1,1,0);

	ostringstream w;
	grid1.if_wall(c1,3,3);
	ASSERT_EQ(c1._pc,3);
}


/**
 * Tests if_wall() when facing SOUTH
 * @param Control_Instructions a fixture
 * @param if_wall_3 test name
 */
TEST(If_Wall_Tests, if_wall_2) {

	Species kahli('k');
	assert(kahli.addInstruction(Instruction(IF_WALL, 3)) == 1);
	assert(kahli.addInstruction(Instruction(HOP)) == 2);
	assert(kahli.addInstruction(Instruction(LEFT, 4)) == 3);
	assert(kahli.addInstruction(Instruction(GO,2)) == 4);

	Creature c1(kahli, SOUTH);

	Darwin grid1(4,3);

	grid1.addCreature(c1,3,2);

	ostringstream w;
	grid1.if_wall(c1,11,3);
	ASSERT_EQ(c1._pc,3);
}

/**
 * Tests if_wall() when facing SOUTH (failure case)
 * @param Control_Instructions a fixture
 * @param if_wall_3 test name
 */
TEST(If_Wall_Tests, if_wall_3) {

	Species kahli('k');
	assert(kahli.addInstruction(Instruction(IF_WALL, 3)) == 1);
	assert(kahli.addInstruction(Instruction(HOP)) == 2);
	assert(kahli.addInstruction(Instruction(LEFT, 4)) == 3);
	assert(kahli.addInstruction(Instruction(GO,2)) == 4);

	Creature c1(kahli, SOUTH);

	Darwin grid1(3,4);

	grid1.addCreature(c1,1,1);

	ostringstream w;
	grid1.if_wall(c1,5,3);
	ASSERT_EQ(c1._pc,0);
}

// ----------
// Left Tests
// ----------

/**
 * Tests the left() function when facing NORTH
 * @param Left_Tests a fixture
 * @param turn_left_1 test name
 */
TEST(Left_Tests, turn_left_1) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, NORTH);
    d.left(c);

    ASSERT_EQ(c._direction, WEST);
}

/**
 * Tests the left() function when facing EAST
 * @param Left_Tests a fixture
 * @param turn_left_2 test name
 */
TEST(Left_Tests, turn_left_2) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, EAST);
    d.left(c);

    ASSERT_EQ(c._direction, NORTH);
}

/**
 * Tests the left() function when facing SOUTH
 * @param Left_Tests a fixture
 * @param turn_left_3 test name
 */
TEST(Left_Tests, turn_left_3) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, SOUTH);
    d.left(c);

    ASSERT_EQ(c._direction, EAST);
}

/**
 * Tests the left() function when facing WEST
 * @param Left_Tests a fixture
 * @param turn_left_4 test name
 */
TEST(Left_Tests, turn_left_4) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, WEST);
    d.left(c);

    ASSERT_EQ(c._direction, SOUTH);
}

// -----------
// Right Tests
// -----------

/**
 * Tests the right() function when facing NORTH
 * @param Right_Tests a fixture
 * @param turn_right_1 test name
 */
TEST(Right_Tests, turn_right_1) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, NORTH);
    d.right(c);

    ASSERT_EQ(c._direction, EAST);
}

/**
 * Tests the right() function when facing EAST
 * @param Right_Tests a fixture
 * @param turn_right_2 test name
 */
TEST(Right_Tests, turn_right_2) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, EAST);
    d.right(c);

    ASSERT_EQ(c._direction, SOUTH);
}

/**
 * Tests the right() function when facing SOUTH
 * @param Right_Tests a fixture
 * @param turn_right_3 test name
 */
TEST(Right_Tests, turn_right_3) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, SOUTH);
    d.right(c);

    ASSERT_EQ(c._direction, WEST);
}

/**
 * Tests the right() function when facing WEST
 * @param Right_Tests a fixture
 * @param turn_right_4 test name
 */
TEST(Right_Tests, turn_right_4) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, WEST);
    d.right(c);

    ASSERT_EQ(c._direction, NORTH);
}

// --------------
// If Empty Tests
// --------------

/**
 * Tests the if_empty() function when facing SOUTH
 * @param If_Empty_Tests a fixture
 * @param if_empty_1 test name
 */
TEST(If_Empty_Tests, if_empty_1) {

	Species kahli('k');
	kahli.addInstruction(Instruction(IF_EMPTY, 3));
	kahli.addInstruction(Instruction(RIGHT, 4));
	kahli.addInstruction(Instruction(HOP));
	kahli.addInstruction(Instruction(GO,0));

	Creature c1(kahli, SOUTH);
	Creature c2(kahli, EAST);

	Darwin grid1(4,3);

	grid1.addCreature(c1,0,1);
	grid1.addCreature(c2,0,0);

	ostringstream w;
	grid1.if_empty(c1,1,3);
	ASSERT_EQ(c1._pc,3);
}

/**
 * Tests the if_empty() function when facing EAST
 * @param If_Empty_Tests a fixture
 * @param if_empty_2 test name
 */
TEST(If_Empty_Tests, if_empty_2) {

	Species kahli('k');
	kahli.addInstruction(Instruction(IF_EMPTY, 3));
	kahli.addInstruction(Instruction(RIGHT, 4));
	kahli.addInstruction(Instruction(HOP));
	kahli.addInstruction(Instruction(GO,0));

	Creature c1(kahli, SOUTH);
	Creature c2(kahli, EAST);

	Darwin grid1(4,3);

	grid1.addCreature(c1,0,1);
	grid1.addCreature(c2,0,0);

	grid1.if_empty(c2,0,0);
	ASSERT_EQ(c1._pc,0);

}

/**
 * Tests the if_empty() function
 * @param If_Empty_Tests a fixture
 * @param if_empty_3 test name
 */
TEST(If_Empty_Tests, if_empty_3) {

	Species kahli('k');
	kahli.addInstruction(Instruction(IF_EMPTY, 3));
	kahli.addInstruction(Instruction(RIGHT, 4));
	kahli.addInstruction(Instruction(HOP));
	kahli.addInstruction(Instruction(GO,0));

	Creature c1(kahli, SOUTH);
	Creature c2(kahli, EAST);
	Creature c3(kahli, NORTH);
	Creature c4(kahli, WEST);
	Darwin grid1(2,2);

	grid1.addCreature(c1,0,0);
	grid1.addCreature(c2,0,1);
	grid1.addCreature(c3,1,0);
	grid1.addCreature(c4,1,1);

	grid1.if_empty(c1,0,0);
	ASSERT_EQ(c1._pc,0);

	grid1.if_empty(c2,1,0);
	ASSERT_EQ(c1._pc,0);

	grid1.if_empty(c3,2,0);
	ASSERT_EQ(c1._pc,0);

	grid1.if_empty(c4,3,0);
	ASSERT_EQ(c1._pc,0);
}

// ---------
// Hop Tests
// ---------

/**
 * Tests hop() when facing NORTH
 * @param Hop_Tests a fixture
 * @param hop_north test name
 */
TEST(Hop_Tests, hop_north) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, NORTH);
	d.addCreature(c, 4);
	d.hop(c, 4);

	ostringstream w;
	w << d << endl;

	ASSERT_EQ(w.str(), " 012\n0.h.\n1...\n2...\n\n");
}

/**
 * Tests hop() when facing SOUTH
 * @param Hop_Tests a fixture
 * @param hop_south test name
 */
TEST(Hop_Tests, hop_south) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, SOUTH);
	d.addCreature(c, 4);
	d.hop(c, 4);

	ostringstream w;
	w << d << endl;

	ASSERT_EQ(w.str(), " 012\n0...\n1...\n2.h.\n\n");
}

/**
 * Tests hop() when facing EAST
 * @param Hop_Tests a fixture
 * @param hop_east test name
 */
TEST(Hop_Tests, hop_east) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, EAST);
	d.addCreature(c, 4);
	d.hop(c, 4);

	ostringstream w;
	w << d << endl;

	ASSERT_EQ(w.str(), " 012\n0...\n1..h\n2...\n\n");
}

/**
 * Tests hop() when facing WEST
 * @param Hop_Tests a fixture
 * @param hop_west test name
 */
TEST(Hop_Tests, hop_west) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, WEST);
	d.addCreature(c, 4);
	d.hop(c, 4);

	ostringstream w;
	w << d << endl;

	ASSERT_EQ(w.str(), " 012\n0...\n1h..\n2...\n\n");
}

/**
 * Tests hop() NORTH w/ wall
 * @param Hop_Tests a fixture
 * @param hop_north_wall test name
 */
TEST(Hop_Tests, hop_north_wall) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, NORTH);
	d.addCreature(c, 1);
	d.hop(c, 1);

	ostringstream w;
	w << d << endl;
	ASSERT_EQ(w.str(), " 012\n0.h.\n1...\n2...\n\n");
}

/**
 * Tests hop() SOUTH w/ wall
 * @param Hop_Tests a fixture
 * @param hop_south_wall test name
 */
TEST(Hop_Tests, hop_south_wall) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, SOUTH);
	d.addCreature(c, 7);
	d.hop(c, 7);

	ostringstream w;
	w << d << endl;
	ASSERT_EQ(w.str(), " 012\n0...\n1...\n2.h.\n\n");
}

/**
 * Tests hop() EAST w/ wall
 * @param Hop_Tests a fixture
 * @param hop_east_wall test name
 */
TEST(Hop_Tests, hop_east_wall) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, EAST);
	d.addCreature(c, 5);
	d.hop(c, 5);

	ostringstream w;
	w << d << endl;
	ASSERT_EQ(w.str(), " 012\n0...\n1..h\n2...\n\n");
}

/**
 * Tests hop() WEST w/ wall
 * @param Hop_Tests a fixture
 * @param hop_west_wall test name
 */
TEST(Hop_Tests, hop_west_wall) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, WEST);
	d.addCreature(c, 3);
	d.hop(c, 3);

	ostringstream w;
	w << d << endl;
	ASSERT_EQ(w.str(), " 012\n0...\n1h..\n2...\n\n");
}

/**
 * Tests hop() NORTH w/ obstacle
 * @param Hop_Tests a fixture
 * @param hop_north_obstacle test name
 */
TEST(Hop_Tests, hop_north_obstacle) {
	Species hopper('h');
	Species food('f');

	Darwin d(3,3);
	Creature c1(food, NORTH);
	Creature c2(hopper, NORTH);

	d.addCreature(c1, 1);
	d.addCreature(c2, 4);
	d.hop(c2, 4);

	ostringstream w;
	w << d << endl;
	ASSERT_EQ(w.str(), " 012\n0.f.\n1.h.\n2...\n\n");
}

/**
 * Tests hop() SOUTH w/ obstacle
 * @param Hop_Tests a fixture
 * @param hop_south_obstacle test name
 */
TEST(Hop_Tests, hop_south_obstacle) {
	Species hopper('h');
	Species food('f');

	Darwin d(3,3);
	Creature c1(food, NORTH);
	Creature c2(hopper, SOUTH);

	d.addCreature(c1, 7);
	d.addCreature(c2, 4);
	d.hop(c2, 4);

	ostringstream w;
	w << d << endl;
	ASSERT_EQ(w.str(), " 012\n0...\n1.h.\n2.f.\n\n");
}

/**
 * Tests hop() EAST w/ obstacle
 * @param Hop_Tests a fixture
 * @param hop_east_obstacle test name
 */
TEST(Hop_Tests, hop_east_obstacle) {
	Species hopper('h');
	Species food('f');

	Darwin d(3,3);
	Creature c1(food, NORTH);
	Creature c2(hopper, EAST);

	d.addCreature(c1, 5);
	d.addCreature(c2, 4);
	d.hop(c2, 4);

	ostringstream w;
	w << d << endl;
	ASSERT_EQ(w.str(), " 012\n0...\n1.hf\n2...\n\n");
}

/**
 * Tests hop() WEST w/ obstacle
 * @param Hop_Tests a fixture
 * @param hop_west_obstacle test name
 */
TEST(Hop_Tests, hop_west_obstacle) {
	Species hopper('h');
	Species food('f');

	Darwin d(3,3);
	Creature c1(food, NORTH);
	Creature c2(hopper, WEST);

	d.addCreature(c1, 3);
	d.addCreature(c2, 4);
	d.hop(c2, 4);

	ostringstream w;
	w << d << endl;
	ASSERT_EQ(w.str(), " 012\n0...\n1fh.\n2...\n\n");
}

// --------
// Go Tests
// --------

/**
 * Tests go() function once, which changes the pc.
 * @param Go_Tests a fixture
 * @param go_1 test name
 */
TEST(Go_Tests, go_1) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, WEST);
	d.go(c, 5);
	ASSERT_EQ(c._pc, 5);
}

/**
 * Tests go() function multiple times, which changes the pc multiple times.
 * @param Go_Tests a fixture
 * @param go_2 test name
 */
TEST(Go_Tests, go_2) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, WEST);
	d.go(c, 5);
	ASSERT_EQ(c._pc, 5);
	d.go(c, 3);
	ASSERT_EQ(c._pc, 3);
	d.go(c, 1);
	ASSERT_EQ(c._pc, 1);
}

// ---------------
// If Random Tests
// ---------------

/**
 * Tests if_random() function, which may change the pc.
 * @param If_Random_Tests a fixture
 * @param if_random_1 test name
 */
TEST(If_Random_Tests, if_random_1) {
	srand(0);
	Species kahli('k');
	assert(kahli.addInstruction(Instruction(IF_RANDOM, 3)) == 1);
	assert(kahli.addInstruction(Instruction(HOP)) == 2);
	assert(kahli.addInstruction(Instruction(LEFT)) == 3);
	assert(kahli.addInstruction(Instruction(GO,2)) == 4);

	Creature k1(kahli, SOUTH);

	Darwin grid1(4,3);
	grid1.addCreature(k1, 2);
	grid1.if_random(k1,3);
	ASSERT_EQ(k1._pc,3);
}

/**
 * Tests if_random() function, which may change the pc.
 * @param If_Random_Tests a fixture
 * @param if_random_2 test name
 */
TEST(If_Random_Tests, if_random_2) {
	srand(0);
	Species kahli('k');
	assert(kahli.addInstruction(Instruction(IF_RANDOM, 5)) == 1);
	assert(kahli.addInstruction(Instruction(HOP)) == 2);
	assert(kahli.addInstruction(Instruction(LEFT)) == 3);
	assert(kahli.addInstruction(Instruction(RIGHT)) == 4);
	assert(kahli.addInstruction(Instruction(LEFT)) == 5);
	assert(kahli.addInstruction(Instruction(GO, 2)) == 6);

	Creature k1(kahli, SOUTH);

	Darwin grid1(4,3);
	grid1.addCreature(k1, 2);
	grid1.if_random(k1,5);
	ASSERT_EQ(k1._pc,5);
}

// --------------
// If Enemy Tests
// --------------

/**
 * Tests if_enemy() function when facing NORTH
 * @param If_Enemy_Tests a fixture
 * @param if_enemy_north test name
 */
TEST(If_Enemy_Tests, if_enemy_north) {
	Species hopper('h');
	Species food('f');

	Darwin d(3,3);
	Creature c1(food, NORTH);
	Creature c2(hopper, NORTH);

	d.addCreature(c1, 1);
	d.addCreature(c2, 4);
	d.if_enemy(c2, 4, 5);
	ASSERT_EQ(c2._pc, 5);
}

/**
 * Tests if_enemy() function when facing SOUTH
 * @param If_Enemy_Tests a fixture
 * @param if_enemy_south test name
 */
TEST(If_Enemy_Tests, if_enemy_south) {
	Species hopper('h');
	Species food('f');

	Darwin d(3,3);
	Creature c1(food, NORTH);
	Creature c2(hopper, SOUTH);

	d.addCreature(c1, 7);
	d.addCreature(c2, 4);
	d.if_enemy(c2, 4, 5);
	ASSERT_EQ(c2._pc, 5);
}

/**
 * Tests if_enemy() function when facing EAST
 * @param If_Enemy_Tests a fixture
 * @param if_enemy_east test name
 */
TEST(If_Enemy_Tests, if_enemy_east) {
	Species hopper('h');
	Species food('f');

	Darwin d(3,3);
	Creature c1(food, NORTH);
	Creature c2(hopper, EAST);

	d.addCreature(c1, 5);
	d.addCreature(c2, 4);
	d.if_enemy(c2, 4, 5);
	ASSERT_EQ(c2._pc, 5);
}

/**
 * Tests if_enemy() function when facing WEST
 * @param If_Enemy_Tests a fixture
 * @param if_enemy_west test name
 */
TEST(If_Enemy_Tests, if_enemy_west) {
	Species hopper('h');
	Species food('f');

	Darwin d(3,3);
	Creature c1(food, NORTH);
	Creature c2(hopper, WEST);

	d.addCreature(c1, 3);
	d.addCreature(c2, 4);
	d.if_enemy(c2, 4, 5);
	ASSERT_EQ(c2._pc, 5);
}

/**
 * Tests if_enemy() function when facing NORTH, failure case
 * @param If_Enemy_Tests a fixture
 * @param if_enemy_north_fail test name
 */
TEST(Control_Instructions, if_enemy_north_fail) {
	Species hopper('h');

	Darwin d(3,3);
	Creature c(hopper, NORTH);

	d.addCreature(c, 4);
	d.if_enemy(c, 4, 5);
	ASSERT_EQ(c._pc, 0);
}

/**
 * Tests if_enemy() function when facing SOUTH, failure case
 * @param If_Enemy_Tests a fixture
 * @param if_enemy_south_fail test name
 */
TEST(Control_Instructions, if_enemy_south_fail) {
	Species hopper('h');

	Darwin d(3,3);
	Creature c(hopper, SOUTH);

	d.addCreature(c, 4);
	d.if_enemy(c, 4, 5);
	ASSERT_EQ(c._pc, 0);
}

/**
 * Tests if_enemy() function when facing EAST, failure case
 * @param If_Enemy_Tests a fixture
 * @param if_enemy_east_fail test name
 */
TEST(Control_Instructions, if_enemy_east_fail) {
	Species hopper('h');

	Darwin d(3,3);
	Creature c(hopper, EAST);

	d.addCreature(c, 4);
	d.if_enemy(c, 4, 5);
	ASSERT_EQ(c._pc, 0);
}

/**
 * Tests if_enemy() function when facing WEST, failure case
 * @param If_Enemy_Tests a fixture
 * @param if_enemy_west_fail test name
 */
TEST(Control_Instructions, if_enemy_west_fail) {
	Species hopper('h');

	Darwin d(3,3);
	Creature c(hopper, WEST);

	d.addCreature(c, 4);
	d.if_enemy(c, 4, 5);
	ASSERT_EQ(c._pc, 0);
}

// ---------------
// Indexable tests
// ---------------

/**
 * Tests at() when given coordinates
 * @param Indexable a fixture
 * @param at_1 test name
 */
TEST(Indexable, at_1) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, SOUTH);
	d.addCreature(c, 1, 1);

	ostringstream a;

	a << d.at(1,1);
	ASSERT_EQ(a.str(), "h");

	ostringstream b;
	b << d.at(0,0);
	ASSERT_EQ(b.str(), ".");
}

/**
 * Tests at() when given a position in row-major array
 * @param Indexable a fixture
 * @param at_2 test name
 */
TEST(Indexable, at_2) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, SOUTH);
	d.addCreature(c, 5);

	ostringstream a;

	a << d.at(5);
	ASSERT_EQ(a.str(), "h");

	ostringstream b;
	b << d.at(0);
	ASSERT_EQ(b.str(), ".");
}

/**
 * Tests at() when given coordinates with multiple creatures
 * @param Indexable a fixture
 * @param at_3 test name
 */
TEST(Indexable, at_3) {
	Species hopper('h');
	Species potato('p');
	Species squash('s');

	Darwin d(3,3);

	Creature c1(hopper, SOUTH);
	Creature c2(potato, SOUTH);
	Creature c3(squash, SOUTH);

	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 1, 1);
	d.addCreature(c3, 2, 2);

	ostringstream a;

	a << d.at(0,0);
	ASSERT_EQ(a.str(), "h");

	ostringstream b;

	b << d.at(1,1);
	ASSERT_EQ(b.str(), "p");

	ostringstream c;

	c << d.at(2,2);
	ASSERT_EQ(c.str(), "s");
}

/**
 * Tests at() when given a position in row-major array with multiple creatures
 * @param Indexable a fixture
 * @param at_4 test name
 */
TEST(Indexable, at_4) {
	Species hopper('h');
	Species potato('p');
	Species squash('s');

	Darwin d(3,3);

	Creature c1(hopper, SOUTH);
	Creature c2(potato, SOUTH);
	Creature c3(squash, SOUTH);

	d.addCreature(c1, 0);
	d.addCreature(c2, 4);
	d.addCreature(c3, 8);

	ostringstream a;

	a << d.at(0);
	ASSERT_EQ(a.str(), "h");

	ostringstream b;

	b << d.at(4);
	ASSERT_EQ(b.str(), "p");

	ostringstream c;

	c << d.at(8);
	ASSERT_EQ(c.str(), "s");
}

/**
 * Tests at() when out of bounds
 * @param Indexable a fixture
 * @param at_5 test name
 */
TEST(Indexable, at_5) {
	Darwin d(3,3);
	try {
        d.at(-1);
    } catch (std::exception& ex) {
       ASSERT_STREQ("n is out of bounds", ex.what());
    }
}

/**
 * Tests at() when out of bounds
 * @param Indexable a fixture
 * @param at_6 test name
 */
TEST(Indexable, at_6) {
	Darwin d(3,3);
	try {
        d.at(9);
    } catch (std::exception& ex) {
       ASSERT_STREQ("n is out of bounds", ex.what());
    }
}

/**
 * Tests at() when out of bounds
 * @param Indexable a fixture
 * @param at_7 test name
 */
TEST(Indexable, at_7) {
	Darwin d(3,3);
	try {
        d.at(-1, -1);
    } catch (std::exception& ex) {
       ASSERT_STREQ("input is out of bounds", ex.what());
    }
}

/**
 * Tests at() when out of bounds
 * @param Indexable a fixture
 * @param at_8 test name
 */
TEST(Indexable, at_8) {
	Darwin d(3,3);
	try {
        d.at(3,3);
    } catch (std::exception& ex) {
       ASSERT_STREQ("input is out of bounds", ex.what());
    }
}

// --------------
// Iterable Tests
// --------------

/**
 * Tests the correctness of the first element of the iterator
 * @param Iterable a fixture
 * @param iterator_1 test name
 */
TEST(Iterable, iterator_1) {
	Darwin d(3, 4);
	Species potato('p');
	Creature c1(potato, NORTH);
	d.addCreature(c1, 0, 0);

	vector<Creature>::iterator it = d.begin();

	ostringstream a;
	a << *it;

	ASSERT_EQ(a.str(), "p");
}

/**
 * Tests the correctness of the size of the iterator
 * @param Iterable a fixture
 * @param iterator_2 test name
 */
TEST(Iterable, iterator_2) {
	Darwin d(3, 4);
	vector<Creature>::iterator b = d.begin();
	vector<Creature>::iterator e = d.end();

	ASSERT_EQ(e, b + d.grid.size());
}

/**
 * Tests iteration
 * @param Iterable a fixture
 * @param iterator_3 test name
 */
TEST(Iterable, iterator_3) {
	Darwin d(4, 4);
	vector<Creature>::iterator b = d.begin();
	vector<Creature>::iterator e = d.end();

	while (b != e)
		b++;

	ASSERT_EQ(b, e);
}

/**
 * Tests iteration over an empty grid
 * @param Iterable a fixture
 * @param iterator_4 test name
 */
TEST(Iterable, iterator_4) {
	Darwin d(4, 4);
	vector<Creature>::iterator b = d.begin();
	vector<Creature>::iterator e = d.end();

	while (b != e) {
		ostringstream a;
		a << *b;
		ASSERT_EQ(a.str(), ".");
		b++;
	}
	
	ASSERT_EQ(b, e);
}

/**
 * Tests iteration and correct values over the iteration
 * @param Iterable a fixture
 * @param iterator_5 test name
 */
TEST(Iterable, iterator_5) {
	Species hopper('h');
	Species potato('p');
	Species squash('s');

	Darwin d(3,3);

	Creature c1(hopper, SOUTH);
	Creature c2(potato, SOUTH);
	Creature c3(squash, SOUTH);

	d.addCreature(c1, 0);
	d.addCreature(c2, 4);
	d.addCreature(c3, 8);

	vector<Creature>::iterator b = d.begin();
	vector<Creature>::iterator e = d.end();

	vector<Creature>::iterator b_copy = b;

	while (b != e) {

		ostringstream a;
		a << *b;

		if (b == b_copy + 0) {
			ASSERT_EQ(a.str(), "h");
		} else if (b == b_copy + 4) {
			ASSERT_EQ(a.str(), "p");
		} else if (b == b_copy + 8) {
			ASSERT_EQ(a.str(), "s");
		} else {
			ASSERT_EQ(a.str(), ".");
		}

		b++;
	}

	ASSERT_EQ(b, e);
}

// ---------------------
// Add Instruction Tests
// ---------------------

/**
 * Tests that a new species should have no instructions
 * @param Add_Instruction a fixture
 * @param add_instruction_1 test name
 */
TEST(Add_Instruction, add_instruction_1) {
	Species hopper('h');
	ASSERT_EQ(hopper.program.size(), 0);
}

/**
 * Tests the addInstruction() function, correctness of the size of the program vector
 * @param Add_Instruction a fixture
 * @param add_instruction_2 test name
 */
TEST(Add_Instruction, add_instruction_2) {
	Species hopper('h');
	hopper.addInstruction(Instruction(HOP));
	ASSERT_EQ(hopper.program.size(), 1);
	hopper.addInstruction(Instruction(HOP));
	ASSERT_EQ(hopper.program.size(), 2);
	hopper.addInstruction(Instruction(LEFT));
	ASSERT_EQ(hopper.program.size(), 3);
	hopper.addInstruction(Instruction(GO,0));
	ASSERT_EQ(hopper.program.size(), 4);
}

/**
 * Tests the addInstruction() function, correctness of the contents of the program vector
 * @param Add_Instruction a fixture
 * @param add_instruction_3 test name
 */
TEST(Add_Instruction, add_instruction_3) {
	Species hopper('h');
	hopper.addInstruction(Instruction(HOP));
	hopper.addInstruction(Instruction(HOP));
	hopper.addInstruction(Instruction(LEFT));
	hopper.addInstruction(Instruction(GO,0));

	ASSERT_EQ(hopper.program[0].instruction_name, HOP);
	ASSERT_EQ(hopper.program[1].instruction_name, HOP);
	ASSERT_EQ(hopper.program[2].instruction_name, LEFT);
	ASSERT_EQ(hopper.program[3].instruction_name, GO);
	ASSERT_EQ(hopper.program[3]._n, 0);
}

/**
 * Tests the addInstruction() function, correctness of the contents of the program vector
 * @param Add_Instruction a fixture
 * @param add_instruction_4 test name
 */
TEST(Add_Instruction, add_instruction_4) {
	Species hopper('h');
	hopper.addInstruction(Instruction(IF_EMPTY, 6));
	hopper.addInstruction(Instruction(HOP));
	hopper.addInstruction(Instruction(IF_WALL, 4));
	hopper.addInstruction(Instruction(IF_RANDOM, 5));

	ASSERT_EQ(hopper.program[0].instruction_name, IF_EMPTY);
	ASSERT_EQ(hopper.program[0]._n, 6);
	ASSERT_EQ(hopper.program[1].instruction_name, HOP);
	ASSERT_EQ(hopper.program[2].instruction_name, IF_WALL);
	ASSERT_EQ(hopper.program[2]._n, 4);
	ASSERT_EQ(hopper.program[3].instruction_name, IF_RANDOM);
	ASSERT_EQ(hopper.program[3]._n, 5);
}

// ---------------------
// Adding Creature Tests
// ---------------------

/**
 * Tests addCreature() when given coordinates
 * @param Add_Creature a fixture
 * @param add_creature_1 test name
 */
TEST(Add_Creature, add_creature_1) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, SOUTH);
	d.addCreature(c, 1,1);

	ostringstream a;

	a << d.grid[4];
	ASSERT_EQ(a.str(), "h");
}

/**
 * Tests addCreature() when given a position in row-major array
 * @param Add_Creature a fixture
 * @param add_creature_2 test name
 */
TEST(Add_Creature, add_creature_2) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, SOUTH);
	d.addCreature(c, 5);

	ostringstream a;

	a << d.grid[5];
	ASSERT_EQ(a.str(), "h");
}

/**
 * Tests addCreature() when given coordinates with multiple creatures
 * @param Add_Creature a fixture
 * @param add_creature_3 test name
 */
TEST(Add_Creature, add_creature_3) {
	Species hopper('h');
	Species potato('p');
	Species squash('s');

	Darwin d(3,3);

	Creature c1(hopper, SOUTH);
	Creature c2(potato, SOUTH);
	Creature c3(squash, SOUTH);

	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 1, 1);
	d.addCreature(c3, 2, 2);

	ostringstream a;

	a << d.grid[0];
	ASSERT_EQ(a.str(), "h");

	ostringstream b;

	b << d.grid[4];
	ASSERT_EQ(b.str(), "p");

	ostringstream c;

	c << d.grid[8];
	ASSERT_EQ(c.str(), "s");
}

/**
 * Tests addCreature() when given a position in row-major array with multiple creatures
 * @param Add_Creature a fixture
 * @param add_creature_4 test name
 */
TEST(Add_Creature, add_creature_4) {
	Species hopper('h');
	Species potato('p');
	Species squash('s');

	Darwin d(3,3);

	Creature c1(hopper, SOUTH);
	Creature c2(potato, SOUTH);
	Creature c3(squash, SOUTH);

	d.addCreature(c1, 0);
	d.addCreature(c2, 4);
	d.addCreature(c3, 8);

	ostringstream a;

	a << d.grid[0];
	ASSERT_EQ(a.str(), "h");

	ostringstream b;

	b << d.grid[4];
	ASSERT_EQ(b.str(), "p");

	ostringstream c;

	c << d.grid[8];
	ASSERT_EQ(c.str(), "s");
}

// ----------------
// Simulation Tests
// ----------------


// -----------------
// Constructor Tests
// -----------------

/**
Testing Action Instruction instance (Constructor)
*/
TEST(Constructors, instruction_1){
	Instruction i(HOP);
	ASSERT_EQ(i.instruction_name, HOP);
	ASSERT_EQ(i._n,-1);
}

/**
Testing Control Instruction instance (Constructor)
*/
TEST(Constructors, instruction_2){
	Instruction i(GO,6);
	ASSERT_EQ(i.instruction_name, GO);
	ASSERT_EQ(i._n,6);
}

/**
Testing Null Species instance
*/
TEST(Constructors, species_1){
	Species s;
	ostringstream v;
	v << s;
	ASSERT_EQ(v.str(), ".");
	ASSERT_EQ(s.program.size(),0);
}
/**
Testing NON Null Species instance
*/
TEST(Constructors, species_2){
	Species s('x');
	ostringstream v;
	v << s;
	ASSERT_EQ(v.str(), "x");
	ASSERT_EQ(s.program.size(),0);
}
/**
Testing Creation (Construction) of multiple Species instances
*/
TEST(Constructors, species_3){
	Species s1('y');
	Species s2('y');
	ostringstream v1;
	ostringstream v2;
	v1 << s1;
	v2 << s2;
	ASSERT_EQ(v1.str(), v2.str());
	ASSERT_EQ(s1.program.size(),s2.program.size());

	s1.addInstruction(Instruction(HOP));

	ASSERT_FALSE(s1.program.size() == s2.program.size());
}
/**
Testing Null Creature cunstructor instance
*/
TEST(Constructors, creature_1){
	Creature c;
	ostringstream v;
	v << c;
	ASSERT_EQ(v.str(), ".");
	// ASSERT_EQ(s.program.size(),0);
}

/**
Testing NON Null Creature cunstructor instance
*/
TEST(Constructors, creature_2){
	// Creature depends on a species
	Species s('k');

	Creature c(s,WEST);
	ostringstream v;
	v << c;
	ASSERT_EQ(v.str(), "k");
	ASSERT_EQ(c._direction, WEST);
	ASSERT_EQ(c._pc,0);
	ASSERT_FALSE(c.isNull);
}

/**
Testing Multiple Creature cunstructor instances
*/
TEST(Constructors, creature_3){
	// Creature depends on a species
	Species s1('k');
	Species s2('p');
	Creature c1(s1,WEST);
	Creature c2(s2,WEST);
	Creature c3;
	ostringstream v1;
	ostringstream v2;
	v1 << c1;
	v2 << c2;
	ASSERT_FALSE(v1.str() == v2.str());
	ASSERT_EQ(c1._direction, c2._direction);
	ASSERT_EQ(c1._pc,c2._pc);
	c1++;
	ASSERT_FALSE(c1._pc == c2._pc);
	ASSERT_FALSE(c1.isNull);
	ASSERT_FALSE(c2.isNull);
	ASSERT_TRUE(c3.isNull);
}

/**
Testing Darwin Grid Construction (square)
*/
TEST(Constructors, darwin_1){
	// Creature depends on a species
	Darwin d(3,3);

	ASSERT_EQ(d.grid.size(), 9);
	ASSERT_EQ(d._row, 3);	
	ASSERT_EQ(d._col, 3);	

	ostringstream v;
	v << d;

	ASSERT_EQ(v.str(), " 012\n0...\n1...\n2...\n");
}

/**
Testing Darwin Grid Construction (rectangle)
*/
TEST(Constructors, darwin_2){
	// Creature depends on a species
	Darwin d(4,3);

	ASSERT_EQ(d.grid.size(), 12);
	ASSERT_EQ(d._row, 4);	
	ASSERT_EQ(d._col, 3);	

	ostringstream v;
	v << d;

	ASSERT_EQ(v.str(), " 012\n0...\n1...\n2...\n3...\n");
}


/**
Testing Complete (multiple) Simulations and the respective states afterwards
*/
TEST(Simulation, simulate_1){
	Species kahli('k');
    assert(kahli.addInstruction(Instruction(IF_ENEMY,3)) == 1);
    assert(kahli.addInstruction(Instruction(LEFT)) == 2);
    assert(kahli.addInstruction(Instruction(GO,0)) == 3);
    assert(kahli.addInstruction(Instruction(INFECT)) == 4);
    assert(kahli.addInstruction(Instruction(GO,0)) == 5);

    Species food('f');
    assert(food.addInstruction(Instruction(LEFT)) == 1);
    assert(food.addInstruction(Instruction(GO,0)) == 2);

    Creature c1(kahli, EAST);
    Creature c2(food, NORTH);

    Darwin d(2,2);

    d.addCreature(c1,1);
    d.addCreature(c2,0);

    ostringstream v1;
    d.simulate(1,v1);
    ASSERT_EQ(v1.str(), "Turn = 0.\n 01\n0fk\n1..\n\nTurn = 1.\n 01\n0fk\n1..\n\n");
    ASSERT_EQ(d.grid.at(1)._direction, NORTH);
    ASSERT_EQ(d.grid.at(0)._direction, WEST);

    ostringstream v2;
    d.simulate(1,v2);

    ASSERT_EQ(v2.str(), "Turn = 0.\n 01\n0fk\n1..\n\nTurn = 1.\n 01\n0fk\n1..\n\n");
    ASSERT_EQ(d.grid.at(1)._direction, WEST);
    ASSERT_EQ(d.grid.at(0)._direction, SOUTH);


    ostringstream v3;
    d.simulate(1,v3);

    ASSERT_EQ(v3.str(), "Turn = 0.\n 01\n0fk\n1..\n\nTurn = 1.\n 01\n0kk\n1..\n\n");
    ASSERT_EQ(d.grid.at(1)._direction, WEST);
    ASSERT_EQ(d.grid.at(0)._direction, EAST);

    ostringstream v4;
    d.simulate(1,v4);

    ASSERT_EQ(v4.str(), "Turn = 0.\n 01\n0kk\n1..\n\nTurn = 1.\n 01\n0kk\n1..\n\n");
    ASSERT_EQ(d.grid.at(1)._direction, SOUTH);
    //ASSERT_EQ(d.grid.at(0)._direction, NORTH);
}
/**
Testing Complete (multiple) Simulations and the respective states afterwards
*/
TEST(Simulation, simulate_2){
	Species kahli('k');
    assert(kahli.addInstruction(Instruction(IF_ENEMY,3)) == 1);
    assert(kahli.addInstruction(Instruction(LEFT)) == 2);
    assert(kahli.addInstruction(Instruction(GO,0)) == 3);
    assert(kahli.addInstruction(Instruction(INFECT)) == 4);
    assert(kahli.addInstruction(Instruction(GO,0)) == 5);

    Species food('f');
    assert(food.addInstruction(Instruction(LEFT)) == 1);
    assert(food.addInstruction(Instruction(GO,0)) == 2);

	Species hopper('h');
	assert(hopper.addInstruction(Instruction(HOP)) == 1);
	assert(hopper.addInstruction(Instruction(GO,0)) == 2);

    Creature c1(kahli, NORTH);
    Creature c2(food, NORTH);
    Creature c3(hopper, WEST);

    Darwin d(2,3);

    d.addCreature(c1,2);
    d.addCreature(c2,1);
    d.addCreature(c3,3);

    ostringstream v1;
    d.simulate(1,v1);

    ASSERT_EQ(v1.str(),"Turn = 0.\n 012\n0.fk\n1h..\n\nTurn = 1.\n 012\n0.fk\n1h..\n\n");
    ASSERT_EQ(d.grid.at(2)._direction, WEST);

    ostringstream v2;
    d.simulate(1,v2);

    ASSERT_EQ(v2.str(),"Turn = 0.\n 012\n0.fk\n1h..\n\nTurn = 1.\n 012\n0.kk\n1h..\n\n");
    ASSERT_EQ(d.grid.at(2)._direction, WEST);

}
/**
Testing Complete (multiple) Simulations and the respective states afterwards
*/
TEST(Simulation, simulate_3){

	Species hopper('h');
	assert(hopper.addInstruction(Instruction(HOP)) == 1);
	assert(hopper.addInstruction(Instruction(RIGHT)) == 2);	
	assert(hopper.addInstruction(Instruction(GO,0)) == 3);

    Creature c1(hopper, EAST);
    Creature c2(hopper, WEST);

    Darwin d(2,2);

    d.addCreature(c1,0);
    d.addCreature(c2,3);

    ostringstream v1;
    d.simulate(1,v1);

    ASSERT_EQ(v1.str(),"Turn = 0.\n 01\n0h.\n1.h\n\nTurn = 1.\n 01\n0.h\n1h.\n\n");
    ASSERT_EQ(d.grid.at(1)._direction, EAST);
    ASSERT_EQ(d.grid.at(2)._direction, WEST);

    ostringstream v2;
    d.simulate(1,v2);

    ASSERT_EQ(v2.str(),"Turn = 0.\n 01\n0.h\n1h.\n\nTurn = 1.\n 01\n0.h\n1h.\n\n");
    ASSERT_EQ(d.grid.at(1)._direction, SOUTH);
    ASSERT_EQ(d.grid.at(2)._direction, NORTH);

    ostringstream v3;
    d.simulate(1,v3);

    ASSERT_EQ(v3.str(),"Turn = 0.\n 01\n0.h\n1h.\n\nTurn = 1.\n 01\n0h.\n1.h\n\n");
    ASSERT_EQ(d.grid.at(0)._direction, NORTH);
    ASSERT_EQ(d.grid.at(3)._direction, SOUTH);

}


