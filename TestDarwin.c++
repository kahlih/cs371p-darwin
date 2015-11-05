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

/* INFECT EAST */
TEST(Action_Instructions, infect_2){

	Species hopper('h');
    assert(hopper.addInstruction(Instruction(HOP)) == 1);
    assert(hopper.addInstruction(Instruction(GO,0)) == 2);

	Species rover('r');
	assert(rover.addInstruction(Instruction(IF_ENEMY, 2)) == 1);
	assert(rover.addInstruction(Instruction(IF_EMPTY, 4)) == 2);
	assert(rover.addInstruction(Instruction(INFECT)) == 3);
	assert(rover.addInstruction(Instruction(HOP)) == 4);
	assert(rover.addInstruction(Instruction(GO,0)) == 5);

	Creature c1(hopper, SOUTH);
	Creature c2(rover, EAST);

	Darwin grid1(4,3);

	grid1.addCreature(c1,0,1);
	grid1.addCreature(c2,1,0);

	// * h *
	// r * *
	// * * *
	// * * *

	ostringstream w;
	grid1.simulate(1,w);
	ASSERT_EQ(w.str(),"Turn = 0.\n 012\n0.h.\n1r..\n2...\n3...\n\nTurn = 1.\n 012\n0...\n1rr.\n2...\n3...\n\n");

}

// /* INFECT NORTH */
TEST(Action_Instructions, infect_3){

    Species food('f');
    assert(food.addInstruction(Instruction(LEFT)) == 1);
    assert(food.addInstruction(Instruction(GO,0)) == 2);

	Species rover('r');
	assert(rover.addInstruction(Instruction(IF_ENEMY, 2)) == 1);
	assert(rover.addInstruction(Instruction(IF_EMPTY, 4)) == 2);
	assert(rover.addInstruction(Instruction(INFECT)) == 3);
	assert(rover.addInstruction(Instruction(HOP)) == 4);
	assert(rover.addInstruction(Instruction(GO,0)) == 5);

	Creature c1(food, WEST);
	Creature c2(rover, NORTH);

	Darwin grid1(2,2);

	grid1.addCreature(c1,0,1);
	grid1.addCreature(c2,1,1);

	ostringstream w;
	grid1.simulate(1,w);
	ASSERT_EQ(w.str(),"Turn = 0.\n 01\n0.f\n1.r\n\nTurn = 1.\n 01\n0.r\n1.r\n\n");

}

/* If_Wall WEST */
TEST(Control_Instructions, if_wall_1) {

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


/* If_Wall SOUTH */
TEST(Control_Instructions, if_wall_2) {

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

/* NOT If_Wall NORTH */
TEST(Control_Instructions, if_wall_3) {

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

/**
 * Tests the left() function when facing NORTH
 */
TEST(Action_Instructions, turn_left_1) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, NORTH);
    d.left(c);

    ASSERT_EQ(c._direction, WEST);
}

/**
 * Tests the left() function when facing EAST
 */
TEST(Action_Instructions, turn_left_2) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, EAST);
    d.left(c);

    ASSERT_EQ(c._direction, NORTH);
}

/**
 * Tests the left() function when facing SOUTH
 */
TEST(Action_Instructions, turn_left_3) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, SOUTH);
    d.left(c);

    ASSERT_EQ(c._direction, EAST);
}

/**
 * Tests the left() function when facing WEST
 */
TEST(Action_Instructions, turn_left_4) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, WEST);
    d.left(c);

    ASSERT_EQ(c._direction, SOUTH);
}

/**
 * Tests the right() function when facing NORTH
 */
TEST(Action_Instructions, turn_right_1) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, NORTH);
    d.right(c);

    ASSERT_EQ(c._direction, EAST);
}

/**
 * Tests the right() function when facing EAST
 */
TEST(Action_Instructions, turn_right_2) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, EAST);
    d.right(c);

    ASSERT_EQ(c._direction, SOUTH);
}

/**
 * Tests the right() function when facing SOUTH
 */
TEST(Action_Instructions, turn_right_3) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, SOUTH);
    d.right(c);

    ASSERT_EQ(c._direction, WEST);
}

/**
 * Tests the right() function when facing WEST
 */
TEST(Action_Instructions, turn_right_4) {
    Species hopper('h');
    Darwin d(1,1);
    Creature c(hopper, WEST);
    d.right(c);

    ASSERT_EQ(c._direction, NORTH);
}


TEST(Control_Instructions, if_empty_1) {

	Species kahli('k');
	assert(kahli.addInstruction(Instruction(IF_EMPTY, 3)) == 1);
	assert(kahli.addInstruction(Instruction(RIGHT, 4)) == 2);
	assert(kahli.addInstruction(Instruction(HOP)) == 3);
	assert(kahli.addInstruction(Instruction(GO,0)) == 4);

	Creature c1(kahli, SOUTH);
	Creature c2(kahli, EAST);

	Darwin grid1(4,3);

	grid1.addCreature(c1,0,1);
	grid1.addCreature(c2,0,0);

	ostringstream w;
	grid1.if_empty(c1,1,3);
	ASSERT_EQ(c1._pc,3);
}

// Not empty test
TEST(Control_Instructions, if_empty_2) {

	Species kahli('k');
	assert(kahli.addInstruction(Instruction(IF_EMPTY, 3)) == 1);
	assert(kahli.addInstruction(Instruction(RIGHT, 4)) == 2);
	assert(kahli.addInstruction(Instruction(HOP)) == 3);
	assert(kahli.addInstruction(Instruction(GO,0)) == 4);

	Creature c1(kahli, SOUTH);
	Creature c2(kahli, EAST);

	Darwin grid1(4,3);

	grid1.addCreature(c1,0,1);
	grid1.addCreature(c2,0,0);

	grid1.if_empty(c2,0,0);
	ASSERT_EQ(c1._pc,0);

}

TEST(Control_Instructions, if_empty_3) {

	Species kahli('k');
	assert(kahli.addInstruction(Instruction(IF_EMPTY, 3)) == 1);
	assert(kahli.addInstruction(Instruction(RIGHT, 4)) == 2);
	assert(kahli.addInstruction(Instruction(HOP)) == 3);
	assert(kahli.addInstruction(Instruction(GO,0)) == 4);

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
/**
 * Tests hopping NORTH
 */
TEST(Action_Instructions, hop_north) {
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
 * Tests hopping SOUTH
 */
TEST(Action_Instructions, hop_south) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, SOUTH);
	d.addCreature(c, 4);
	d.hop(c, 4);

	ostringstream w;
	w << d << endl;

	ASSERT_EQ(w.str(), " 012\n0...\n1...\n2.h.\n\n");
}

// /**
//  * Tests hopping EAST
//  */
TEST(Action_Instructions, hop_east) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, EAST);
	d.addCreature(c, 4);
	d.hop(c, 4);

	ostringstream w;
	w << d << endl;

	ASSERT_EQ(w.str(), " 012\n0...\n1..h\n2...\n\n");
}

// /**
//  * Tests hopping WEST w/ obstacle or wall
//  */
TEST(Action_Instructions, hop_west) {
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
 * Tests hopping NORTH w/ wall
 */
TEST(Action_Instructions, hop_north_wall) {
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
 * Tests hopping SOUTH w/ wall
 */
TEST(Action_Instructions, hop_south_wall) {
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
 * Tests hopping EAST w/ wall
 */
TEST(Action_Instructions, hop_east_wall) {
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
 * Tests hopping WEST w/ wall
 */
TEST(Action_Instructions, hop_west_wall) {
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
 * Tests hopping NORTH w/ obstacle
 */
TEST(Action_Instructions, hop_north_obstacle) {
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
 * Tests hopping SOUTH w/ obstacle
 */
TEST(Action_Instructions, hop_south_obstacle) {
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
 * Tests hopping EAST w/ obstacle
 */
TEST(Action_Instructions, hop_east_obstacle) {
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
 * Tests hopping WEST w/ obstacle
 */
TEST(Action_Instructions, hop_west_obstacle) {
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

/**
 * Tests go once, which changes the pc.
 */
TEST(Control_Instructions, go_1) {
	Species hopper('h');
	Darwin d(3,3);
	Creature c(hopper, WEST);
	d.go(c, 5);
	ASSERT_EQ(c._pc, 5);
}

/**
 * Tests go multiple times, which changes the pc multiple times.
 */
TEST(Control_Instructions, go_2) {
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

//if_random
TEST(Control_Instructions, if_random_1) {
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

//if_random
TEST(Control_Instructions, if_random_2) {
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

/**
 * Tests checking for enemy when facing NORTH
 */
TEST(Control_Instructions, if_enemy_north) {
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
 * Tests checking for enemy when facing SOUTH
 */
TEST(Control_Instructions, if_enemy_south) {
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
 * Tests checking for enemy when facing EAST
 */
TEST(Control_Instructions, if_enemy_east) {
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
 * Tests checking for enemy when facing WEST
 */
TEST(Control_Instructions, if_enemy_west) {
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
 * Tests checking for enemy when facing NORTH
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
 * Tests checking for enemy when facing SOUTH
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
 * Tests checking for enemy when facing EAST
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
 * Tests checking for enemy when facing WEST
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

	// ASSERT_EQ(*it, c1);
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

// -----------------
// Constructor Tests
// -----------------

// ---------------------
// Adding Creature Tests
// ---------------------

// ----------------
// Simulation Tests
// ----------------