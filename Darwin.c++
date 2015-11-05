#include "Darwin.h"
#include <iostream>
#include <deque>
#include <stdexcept> // invalid_argument
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
			if ((location+_col < _row*_col) && (grid.at(location+_col).isNull)){
				grid.at(location+_col) = c;
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
			if ((location-_col >= 0) && (grid.at(location-_col).isNull)) {
				grid.at(location-_col) = c;
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
void Darwin::infect(Creature& c, int location) {
	switch(c._direction){
		case WEST: {
				bool invalid = (location-1) % (_col) == (_col-1);
				if (!invalid && !grid.at(location-1).isNull) {
					Creature& neighbor = grid.at(location - 1);
					if (neighbor._species._name != '.' && neighbor._species._name != c._species._name) {
						neighbor._species = c._species;
						neighbor._pc = 0;
					}				}
			}
			break;
		case SOUTH:
			if ((location+_col < _row*_col) && (!grid.at(location+_col).isNull)){
				Creature& neighbor = grid.at(location+_row);
				if (neighbor._species._name != '.' && neighbor._species._name != c._species._name) {
					neighbor._species = c._species;
					neighbor._pc = 0;
				}
			}
			break;
		case EAST: {
				bool invalid = (location+1) % (_col) == 0;
				if (!invalid && !grid.at(location+1).isNull) {
					Creature& neighbor = grid.at(location + 1);
					if (neighbor._species._name != '.' && neighbor._species._name != c._species._name) {
						neighbor._species = c._species;
						neighbor._pc = 0;
					}					}
			}
			break;
		case NORTH:
			if ((location-_col >= 0) && (!grid.at(location-_col).isNull)) {
				Creature& neighbor = grid.at(location-_col);
				if (neighbor._species._name != '.' && neighbor._species._name != c._species._name) {
					neighbor._species = c._species;
					neighbor._pc = 0;
				}
			}
			break;
	}
}
void Darwin::if_enemy(Creature& c, int location, int n) {
	switch(c._direction){
		case WEST: {
				bool invalid = (location-1) % (_col) == (_col-1);
				if (!invalid && !grid.at(location-1).isNull) {
					go(c, n);
				}
			}
			break;
		case SOUTH:
			if ((location+_col < _row*_col) && (!grid.at(location+_col).isNull)){
				go(c, n);
			}
			break;
		case EAST: {
				bool invalid = (location+1) % (_col) == 0;
				if (!invalid && !grid.at(location+1).isNull) {
					go(c, n);
				}
			}
			break;
		case NORTH:
			if ((location-_col >= 0) && (!grid.at(location-_col).isNull)) {
				go(c, n);
			}
			break;
	}
}
void Darwin::if_empty(Creature& c, int location, int n){
	switch(c._direction){
		case WEST: {
				bool invalid = (location-1) % (_col) == (_col-1);
				if (!invalid && grid.at(location-1).isNull) {
					go(c, n);
				}
			}
			break;
		case SOUTH:
			if ((location+_col < _row*_col) && (grid.at(location+_col).isNull)){
				go(c, n);
			}
			break;
		case EAST: {
				bool invalid = (location+1) % (_col) == 0;
				if (!invalid && grid.at(location+1).isNull) {
					go(c, n);
				}
			}
			break;
		case NORTH:
			if ((location-_col >= 0) && (grid.at(location-_col).isNull)) {
				go(c, n);
			}
			break;
	}
}
void Darwin::if_wall(Creature& c, int location, int n){
	switch(c._direction){
		case WEST: {
				bool invalid = (location-1) % (_col) == (_col-1);
				if (invalid) {
					go(c, n);
				}
			}
			break;
		case SOUTH:
			if ((location+_col >= _row*_col)){
				go(c, n);
			}
			break;
		case EAST: {
				bool invalid = (location+1) % (_col) == 0;
				if (invalid) {
					go(c, n);
				}
			}
			break;
		case NORTH:
			if ((location-_col < 0)) {
				go(c, n);
			}
			break;
	}
}
void Darwin::if_random(Creature& c, int n) {
	if (rand() % 2 == 1) {
		go(c, n);
	}
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
void Darwin::addCreature(Creature& c, int n){
	grid[n] = c;
}
Darwin::iterator Darwin::begin(){
	return grid.begin();
}
Darwin::iterator Darwin::end(){
	return grid.end();
}
void Darwin::simulate(int n, ostream& w){
	w << "Turn = " << 0 << "." << endl;
	w << *this;
	w << endl;
	for (int i = 1; i <= n; i++){ // # of turns
		if (i < 10 || (i >= 10 && i%100==0)){
			w << "Turn = " << i << "." << endl;}
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
		for (iter it = list_of_creatures.begin(); it != list_of_creatures.end(); it++){
			pair<int,Creature> cur = *it;
			run(cur.first, cur.second);
		}
		if (i < 10 || (i >= 10 && i%100==0)){
			w << *this;
			w << endl;}
	}
}
void Darwin::run(int location, Creature& c) {
	int pc = c++;
	Instruction i = c.getInstruction(pc);
	// cout << i.instruction_name << " " << c << " " << pc << endl;  

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
			infect(c, location);
			break;

		/* Controls */
		case GO :
			go(c,i._n);
			run(location, c);
			break;
		case IF_EMPTY: 
			if_empty(c, location, i._n);
			run(location, c);
			break;
		case IF_WALL: 
			if_wall(c, location, i._n);
			run(location, c);
			break;
		case IF_RANDOM: 
			if_random(c, i._n);
			run(location, c);
			break;
		case IF_ENEMY: 
			if_enemy(c, location, i._n);
			run(location, c);
			break;

	}
}
Creature& Darwin::at(int n){
	if (n < 0 || n >= _row * _col) {
		throw invalid_argument("n is out of bounds");
	}
	return grid[n];
}
Creature& Darwin::at(int x, int y){
	if (x < 0 || y < 0 || x >= _row || y >= _col) {
		throw invalid_argument("input is out of bounds");
	}
	return grid[x + y*_col];
}
ostream& operator<<(ostream& os, const Darwin& d) {
	int length = d.grid.size()/d._row;
	os << " ";
	for (int i = 0; i < length; i++){
		os << i % 10;
	}

	os << endl;
	for (int i = 0; i < (int)d.grid.size(); i++) {
		if (i % length == 0) {
			os << (i / length) % 10;
		}
		os << d.grid.at(i);
		if (i % length == length - 1) {
			os << endl;
		}
	}
	return os;
}