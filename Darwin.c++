#include "Darwin.h"
#include <iostream>
 #include <deque>
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
	isNull = true;
}
Creature::Creature(Species species, DIRECTION direction) {
	_species = species;
	_direction = direction;
	_pc = 0;
	isNull = false;
}
Creature::~Creature(){}
void Darwin::hop(Creature& c, int location){
	switch(c._direction){
		case WEST: {
				bool invalid = (location-1) % (_col) == (_col-1);
				if (!invalid && grid.at(location-1).isNull) {
					grid.at(location-1) = c;
					grid.at(location) = Creature();
				}
			}
			break;
		case SOUTH:
			if ((location+_row < _row*_col) && (grid.at(location+_row).isNull)){
				grid.at(location+_row) = c;
				grid.at(location) = Creature();
			}
			break;
		case EAST: {
				bool invalid = (location+1) % (_col) == 0;
				if (!invalid && grid.at(location+1).isNull) {
					grid.at(location+1) = c;
					grid.at(location) = Creature();
				}
			}
			break;
		case NORTH:
			if ((location-_row >= 0) && (grid.at(location-_row).isNull)) {
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
void Darwin::right(Creature& c){
	switch(c._direction){
		case WEST: 
			c._direction = NORTH;
			break;
		case SOUTH:
			c._direction = WEST;
			break;
		case EAST:
			c._direction = SOUTH;
			break;
		case NORTH:
			c._direction = EAST;
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
		// Way to not modify the grid
		// Grab all the Creatures that need to be process, THEN process their instruction
		std::deque<pair<int,Creature>> list_of_creatures;
		for (int j = 0; j < (int) grid.size(); j++) {
			Creature& current = at(j);
			if(!current.isNull) {
				pair<int,Creature> p(j,current);
				list_of_creatures.push_back(p);
			}
		}
		// Now process creatures
		typedef deque<pair<int,Creature>>::iterator iter;
		for (iter i = list_of_creatures.begin(); i != list_of_creatures.end(); i++){
			pair<int,Creature> cur = *i;
			run(cur.first, cur.second);
		}
	}
}
void Darwin::run(int location, Creature& c) {
	int pc = c++;
	Instruction i = c.getInstruction(pc);
	//cout << i.instruction_name << " " << c << " " << pc << endl;  

	switch(i.instruction_name){
		/* Actions */
		case HOP : 
			hop(c,location);
			break;
		case LEFT: 
			left(c);
			break;
		case RIGHT: 
			right(c);
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
