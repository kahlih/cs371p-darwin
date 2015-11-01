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
	ASSERT_EQ(s.addInstruction(Action(HOP)), 1);
	ASSERT_EQ(s.addInstruction(Action(HOP)), 2);
	ASSERT_EQ(s.addInstruction(Action(LEFT)), 3);
	ASSERT_EQ(s.addInstruction(Control(GO,0)), 4);
	ASSERT_EQ(s._name,'h');
}

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */



// TEST(Species, species_1){
// 	Action i(HOP);
// 	Species s;
// 	s.addInstruction(i);
	
// 	Creature b1(s,EAST,0);

// 	x.addCreature
// }