// ------------------------------
// Darwin.h
// Copyright (C) 2015
// Kahli Holmes
// Phillip Pan
// ------------------------------


#include <vector>
#include <iostream>
#include "gtest/gtest_prod.h"

using namespace std;

enum INSTRUCTION_NAME {HOP, LEFT, RIGHT, INFECT, IF_EMPTY, IF_WALL, IF_RANDOM, IF_ENEMY, GO};
enum DIRECTION {WEST, NORTH, EAST, SOUTH};

class Instruction {
	friend class Creature;
	friend class Darwin;

	public:
		Instruction(INSTRUCTION_NAME name,int n=-1);
		Instruction();

		FRIEND_TEST(Add_Instruction, add_instruction_3);
		FRIEND_TEST(Add_Instruction, add_instruction_4);

	private:
		INSTRUCTION_NAME instruction_name;
		int _n;
};

class Species {
	friend class Creature;
	friend class Darwin;

	public:
		Species();
	    Species(char c);
		int addInstruction(Instruction instruction);
	    friend ostream& operator<<(ostream& os, const Species& species);

	    FRIEND_TEST(Add_Instruction, add_instruction_1);
	    FRIEND_TEST(Add_Instruction, add_instruction_2);
	    FRIEND_TEST(Add_Instruction, add_instruction_3);
	    FRIEND_TEST(Add_Instruction, add_instruction_4);

	private:
		vector<Instruction> program;
		char _name;
};

class Creature {
	friend class Darwin;

	public:
		Creature();
		Creature(Species species, DIRECTION direction);
		Creature(Species species, DIRECTION direction, int n);
		Instruction& getInstruction(int pc);
		friend ostream& operator<<(ostream& os, const Creature& creature);
		int operator++(int);
		~Creature();

		FRIEND_TEST(Right_Tests, turn_right_1);
		FRIEND_TEST(Right_Tests, turn_right_2);
		FRIEND_TEST(Right_Tests, turn_right_3);
		FRIEND_TEST(Right_Tests, turn_right_4);
		FRIEND_TEST(Go_Tests, go_1);
		FRIEND_TEST(Go_Tests, go_2);
		FRIEND_TEST(If_Wall_Tests, if_wall_1);
		FRIEND_TEST(If_Wall_Tests, if_wall_2);
		FRIEND_TEST(If_Wall_Tests, if_wall_3);
		FRIEND_TEST(Left_Tests, turn_left_1);
		FRIEND_TEST(Left_Tests, turn_left_2);
		FRIEND_TEST(Left_Tests, turn_left_3);
		FRIEND_TEST(Left_Tests, turn_left_4);
		FRIEND_TEST(If_Empty_Tests, if_empty_1);
		FRIEND_TEST(If_Empty_Tests, if_empty_2);
		FRIEND_TEST(If_Empty_Tests, if_empty_3);
		FRIEND_TEST(If_Random_Tests, if_random_1);
		FRIEND_TEST(If_Random_Tests, if_random_2);
		FRIEND_TEST(If_Enemy_Tests, if_enemy_north);
		FRIEND_TEST(If_Enemy_Tests, if_enemy_south);
		FRIEND_TEST(If_Enemy_Tests, if_enemy_west);
		FRIEND_TEST(If_Enemy_Tests, if_enemy_east);
		FRIEND_TEST(Control_Instructions, if_enemy_north_fail);
		FRIEND_TEST(Control_Instructions, if_enemy_south_fail);
		FRIEND_TEST(Control_Instructions, if_enemy_west_fail);
		FRIEND_TEST(Control_Instructions, if_enemy_east_fail);

	private:
		DIRECTION _direction;
		int _pc;
		Species _species;
		bool isNull;
};


class Darwin {

	public:
		typedef vector<Creature>::iterator iterator;
		Darwin(int col, int row);
		~Darwin();
		void addCreature(Creature& c, int x, int y);
		void addCreature(Creature& c, int n);
		iterator begin();
		iterator end();
		void simulate(int n, ostream& w);
		Creature& at(int n);
		Creature& at(int x, int y);
		void run(int location, Creature& c);
		friend ostream& operator<<(ostream& os, const Darwin& d);
		void left(Creature& c);
		void right(Creature& c);
		void go(Creature& c, int n);
		void hop(Creature& c,int location);
		void infect(Creature& c, int location);
		void if_enemy(Creature& c, int location, int n);
		void if_empty(Creature& c, int location, int n);
		void if_wall(Creature& c, int location, int n);
		void if_random(Creature&c, int n);

		FRIEND_TEST(Iterable, iterator_2);
		FRIEND_TEST(Add_Creature, add_creature_1);
		FRIEND_TEST(Add_Creature, add_creature_2);
		FRIEND_TEST(Add_Creature, add_creature_3);
		FRIEND_TEST(Add_Creature, add_creature_4);

	private:
		vector<Creature> grid;
		int _row;
		int _col;
};