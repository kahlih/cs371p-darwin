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
		Instruction(INSTRUCTION_NAME name) {
			instruction_name = name;
		}

		Instruction() {}
	private:
		INSTRUCTION_NAME instruction_name;
};

class Action : public Instruction {
	public:
		Action() {}

	Action(INSTRUCTION_NAME name) : Instruction(name) {}
};

class Control : public Instruction {
	public:
		Control(int n);
	private:
		int _n;

	Control(int n, INSTRUCTION_NAME name) : Instruction(name) {
		_n = n;
	}
};

class Species {
	public:
		void addInstruction(Instruction instruction) {
			program.push_back(instruction);
	    }

	    Species() {}

	private:
		vector<Instruction> program;

};

class Creature {
	private:
		DIRECTION _direction;
		int _pc;
		Species _species;

	public:
		Creature() {}

		Creature(Species species, DIRECTION direction, int n) {
			_species = species;
			_direction = direction;
			_pc = 0;
		}

};

class Darwin {
	public:
		Darwin(int width, int height) : grid(width*height) {
			_width = width;
		}
		
		void addCreature(Creature& c, int x, int y){
			grid[x*_width + y] = c;
		}

		Creature& at(int x, int y){
			return grid[x*_width + y];
		}

	private:
		vector<Creature> grid; //row-major order
		int _width;
};