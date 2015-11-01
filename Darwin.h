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
		Control(INSTRUCTION_NAME name,int n);
	private:
		int _n;
};

class Species {
	public:
		int addInstruction(Instruction instruction);
		Species();
	    Species(char c);
	    char _name;
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
		Creature(Species species, DIRECTION direction);
		Creature(Species species, DIRECTION direction, int n);
		friend ostream& operator<<(ostream& os, const Creature& creature);
		~Creature();
};

class Darwin {
	public:
		Darwin(int col, int row);
		~Darwin();
		void addCreature(Creature& c, int x, int y);
		Creature& at(int n);	// if you have the specific index
		Creature& at(int x, int y);   // if you have coordinates
		void display();
	private:
		vector<Creature> grid; //row-major order
		int _row;
		int _col;
};