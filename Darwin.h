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
enum DIRECTION {NORTH, SOUTH, EAST, WEST};

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

// class Action : public Instruction {
// 	public:
// 		Action();
// 		Action(INSTRUCTION_NAME name);
// };

// class Control : public Instruction {
// 	public:
// 		Control(INSTRUCTION_NAME name,int n);
// 	// private:
// 		int _n;
// };

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
		int _pc;
		Species _species;

	public:
		bool empty;
		Creature();
		Creature(Species species, DIRECTION direction);
		Creature(Species species, DIRECTION direction, int n);
		Instruction& getInstruction(int pc);
		friend ostream& operator<<(ostream& os, const Creature& creature);
		int operator++(int);
		~Creature();
};

class Darwin {
	public:
		typedef vector<Creature>::iterator iterator;
		Darwin(int col, int row);
		~Darwin();
		void addCreature(Creature& c, int x, int y);
		iterator begin();
		iterator end();
		void simulate(int n);
		Creature& at(int n);	// if you have the specific index
		Creature& at(int x, int y);   // if you have coordinates
		void run(int location, Creature& c);
		void display();
		void left(Creature& c);
		void go(Creature& c, int n);
		void hop(Creature& c,int location);
	private:
		vector<Creature> grid; //row-major order
		int _row;
		int _col;
};