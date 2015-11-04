// ------------------------------
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
		bool isControl();
	private:
		INSTRUCTION_NAME instruction_name;
		int _n;
};

class Species {
	friend class Creature;
	public:
		Species();
	    Species(char c);
		int addInstruction(Instruction instruction);
	    char _name;
	private:
		vector<Instruction> program;
};

class Creature {
	friend class Darwin;
	private:
		DIRECTION _direction;

		FRIEND_TEST(Action_Instructions, if_wall_1);
		FRIEND_TEST(Action_Instructions, if_wall_2);
		FRIEND_TEST(Action_Instructions, if_wall_3);
		FRIEND_TEST(Control_Instructions, if_empty_1);
		FRIEND_TEST(Control_Instructions, if_empty_2);
		FRIEND_TEST(Control_Instructions, if_empty_3);
		int _pc;
		Species _species;
		bool isNull;

	public:
		Creature();
		Creature(Species species, DIRECTION direction);
		Creature(Species species, DIRECTION direction, int n);
		Instruction& getInstruction(int pc);
		friend ostream& operator<<(ostream& os, const Creature& creature);
		int operator++(int);
		~Creature();
		FRIEND_TEST(Action_Instructions, turn_left_1);
		FRIEND_TEST(Action_Instructions, turn_left_2);
		FRIEND_TEST(Action_Instructions, turn_left_3);
		FRIEND_TEST(Action_Instructions, turn_left_4);
		FRIEND_TEST(Action_Instructions, turn_right_1);
		FRIEND_TEST(Action_Instructions, turn_right_2);
		FRIEND_TEST(Action_Instructions, turn_right_3);
		FRIEND_TEST(Action_Instructions, turn_right_4);
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
		Creature& at(int n);	// if you have the specific index
		Creature& at(int x, int y);   // if you have coordinates
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
	private:
		vector<Creature> grid; //row-major order
		int _row;
		int _col;
};