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
void Darwin::hop(Creature& c, int location){
	switch(c._direction){
		case WEST: {
				bool invalid = (location-1) % (_col) == (_col-1);
				if (!invalid && grid.at(location-1).empty) {
					grid.at(location-1) = c;
					grid.at(location) = Creature();
				}
			}
			break;
		case SOUTH:
			// if ((location+_row < _row*_col) && (grid.at(location+_row).empty)){
			// 	grid.at(location+_row) = c;
			// 	grid.at(location) = Creature();
			// }
			break;
		case EAST: 
				// grid.at(location+1) = c;
				// grid.at(location) = Creature();
			break;
		case NORTH:
			if ((location-_row >= 0) && (grid.at(location-_row).empty)){
				grid.at(location-_row) = c;
				grid.at(location) = Creature();
			}
			break;
	}
}
void Darwin::left(Creature& c){
	switch(c._direction){
		case WEST: 
			c._direction = SOUTH;
			break;
		case SOUTH:
			c._direction = EAST;
			break;
		case EAST:
			c._direction = NORTH;
			break;
		case NORTH:
			c._direction = WEST;
			break;
	}
}
void Darwin::go(Creature& c, int n) {
	c._pc = n;
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
Darwin::Darwin(int row, int col) : grid(row*col) {
	_row = row;
	_col = col;
}
Darwin::~Darwin(){}
void Darwin::addCreature(Creature& c, int x, int y){
	grid[y + x*_col] = c;
}
Darwin::iterator Darwin::begin(){
	return grid.begin();
}
Darwin::iterator Darwin::end(){
	return grid.end();
}
void Darwin::simulate(int n){
	for (int i = 0; i < n; i++){ // # of turns
		cout << "Turn = " << i << "." << endl;
		display();
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
	cout << i.instruction_name << " " << c << " " << pc << endl;  

	switch(i.instruction_name){
		/* Actions */
		case HOP : 
			hop(c,location);
			break;
		case LEFT: 
			left(c);
			break;
		case RIGHT: 
			break;
		case INFECT: 
			break;

		/* Controls */
		case GO :
			go(c,i._n);
			run(location, c);
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
