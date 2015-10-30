#include "Darwin.h"

Instruction::Instruction(){}
Instruction::Instruction(INSTRUCTION_NAME name) {
	instruction_name = name;
}
Action::Action(){}
Action::Action(INSTRUCTION_NAME name) : Instruction(name) {}

Control::Control(int n, INSTRUCTION_NAME name) : Instruction(name) {
	_n = n;
}

Species::Species() {}
void Species::addInstruction(Instruction instruction) {
	program.push_back(instruction);
}

Creature::Creature() {}
Creature::Creature(Species species, DIRECTION direction, int n) {
	_species = species;
	_direction = direction;
	_pc = 0;
}

Darwin::Darwin(int width, int height) : grid(width*height) {
	_width = width;
}

void Darwin::addCreature(Creature& c, int x, int y){
	grid[x*_width + y] = c;
}

Creature& Darwin::at(int x, int y){
	return grid[x*_width + y];
}
