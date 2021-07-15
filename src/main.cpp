#include <iostream>
#include <DungeonGame/Dungeon/Generator.hpp>

using namespace Dungeon;

int main(int argc, char* argv[]) {
	Generator generator(Dungeons::BSP,80,40,3); // (Dungeons &_type,const int & _width,const int & _height, const int & _depth)
	bool s = generator.generateDungeon();
	if(s)generator.print();
	else std::cout<<"error";
	return 0;
}