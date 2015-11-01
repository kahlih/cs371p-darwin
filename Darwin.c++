#include "Darwin.h"
#include <iostream>

using namespace std;

/* Instruction */
Instruction::Instruction(){}
Instruction::Instruction(INSTRUCTION_NAME name) {
	instruction_name = name;
}
Action::Action(){}
Action::Action(INSTRUCTION_NAME name) : Instruction(name) {}

Control::Control(INSTRUCTION_NAME name,int n) : Instruction(name) {
	_n = n;
}

/* Species */
Species::Species() { _name = '.';}
Species::Species(char c) { _name = c;}
int Species::addInstruction(Instruction instruction) {
	program.push_back(instruction);
	return program.size();
}

/* Creature */
Creature::Creature() {}
Creature::Creature(Species species, DIRECTION direction) {
	_species = species;
	_direction = direction;
	_pc = 0;
}
Creature::Creature(Species species, DIRECTION direction, int n) {
	_species = species;
	_direction = direction;
	_pc = 0;
}
Creature::~Creature(){}

ostream& operator<<(ostream& os, const Creature& creature) {
	os << creature._species._name;
	return os;
}


/* Darwin */
Darwin::Darwin(int col, int row) : grid(row*col) {
	_row = row;
	_col = col;
}
Darwin::~Darwin(){}
void Darwin::addCreature(Creature& c, int x, int y){
	grid[x + y*_col] = c;
}
void Darwin::display(){
	int length = grid.size()/_row;
	cout << " ";
	for (int i = 0; i < length; i++){
		cout << i % 10;
	}

	cout << endl;
	for (int i = 0; i < (int)grid.size(); i++) {
		if (i % length == 0) {
			cout << (i / length) % 10;
		}
		cout << grid.at(i);
		if (i % length == length - 1) {
			cout << endl;
		}
	}

}
Creature& Darwin::at(int n){
	return grid[n];
}
Creature& Darwin::at(int x, int y){
	return grid[x + y*_col];
}
