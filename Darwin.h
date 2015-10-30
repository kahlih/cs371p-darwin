// ------------------------------
// Copyright (C) 2015
// Kahli Holmes
// Phillip Pan
// ------------------------------


#include <vector>
#include "gtest/gtest_prod.h"

using namespace std;

enum INSTRUCTION_NAME {HOP, LEFT, RIGHT, INFECT, IF_EMPTY, IF_WALL, IF_RANDOM, IF_ENEMY, GO};
enum DIRECTION {NORTH, SOUTH, EAST, WEST};

class Instruction {
	public:
		Instruction(INSTRUCTION_NAME name);
		Instruction();
	private:
		INSTRUCTION_NAME instruction_name;
};

class Action : public Instruction {
	public:
		Action();
		Action(INSTRUCTION_NAME name);
};

class Control : public Instruction {
	public:
		Control(int n, INSTRUCTION_NAME name);
	private:
		int _n;
};

class Species {
	public:
		void addInstruction(Instruction instruction);
	    Species();
	private:
		vector<Instruction> program;
};

class Creature {
	private:
		DIRECTION _direction;
		int _pc;
		Species _species;

	public:
		Creature();
		Creature(Species species, DIRECTION direction, int n);
};

class Darwin {
	public:
		Darwin(int width, int height);
		void addCreature(Creature& c, int x, int y);
		Creature& at(int x, int y);
	private:
		vector<Creature> grid; //row-major order
		int _width;
};