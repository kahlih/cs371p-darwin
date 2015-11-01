#include "Darwin.h"
#include <iostream>

/* Instruction */
Instruction::Instruction(){}
Instruction::Instruction(INSTRUCTION_NAME name, int n) {
	instruction_name = name;
	_n = n;
}
bool Instruction::isControl(){
	return (_n>-1);
}
// Action::Action(){}
// Action::Action(INSTRUCTION_NAME name) : Instruction(name) {}

// Control::Control(INSTRUCTION_NAME name,int n) : Instruction(name) {}

/* Species */
Species::Species() { _name = '.';}
Species::Species(char c) { _name = c; }
int Species::addInstruction(Instruction instruction) {
	program.push_back(instruction);
	return program.size();
}
Instruction& Creature::getInstruction(int pc){
	return _species.program[pc];
}

/* Creature */
Creature::Creature() {
	empty = true;
}
Creature::Creature(Species species, DIRECTION direction) {
	_species = species;
	_direction = direction;
	_pc = 0;
	empty = false;
}
Creature::Creature(Species species, DIRECTION direction, int n) {
	_species = species;
	_direction = direction;
	_pc = 0;
	empty = false;
}
Creature::~Creature(){}
void Creature::left(){
	switch(_direction){
		case WEST: 
			_direction = SOUTH;
			break;
		case SOUTH:
			_direction = EAST;
			break;
		case EAST:
			_direction = NORTH;
			break;
		case NORTH:
			_direction = WEST;
			break;
	}
}
void Creature::go(int n) {
	this->_pc = n;
}
ostream& operator<<(ostream& os, const Creature& creature) {
	os << creature._species._name;
	return os;
}
int Creature::operator++(int){
	int t = _pc;
	++this->_pc;
	return t;
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
Darwin::iterator Darwin::begin(){
	return grid.begin();
}
Darwin::iterator Darwin::end(){
	return grid.end();
}
void Darwin::simulate(int n){
	for (int i = 0; i < n; i++){ // # of turns
		for (int j = 0; j < (int) grid.size(); j++) {
			Creature& current = at(j);
			// if (strcmp(current._species._name,'.') != 0){
			// 	cout << current << " i : " << i << endl;
			// }
			if(!current.empty) {
				run(j,current);
			}
		}
		cout << endl;
	}
}
void Darwin::run(int location, Creature& c) {
	// get the pc (creature)
	int pc = c++;
	Instruction i = c.getInstruction(pc);
	switch(i.instruction_name){
		/* Actions */
		case HOP : 
			break;
		case LEFT: 
			c.left();
			break;
		case RIGHT: 
			break;
		case INFECT: 
			break;

		/* Controls */
		case GO :
			c.go(i._n);
			break;
		case IF_EMPTY: 
			break;
		case IF_WALL: 
			break;
		case IF_RANDOM: 
			break;
		case IF_ENEMY: 
			break;

	}
	cout << "Name: " << i.instruction_name << " " << c << " " << pc << endl;  
	// get the instruction from program (species)

	// execute the instruction (switch case)
	// increment the pc (creature)
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
