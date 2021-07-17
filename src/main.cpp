#include <DungeonGame/Dungeon/Dungeon.hpp>
#include <DungeonGame/utill/Input.hpp>

#include <iostream>
#include <cstdlib>
#include <vector>



using namespace LinuxGame;



int main(int argc, char* argv[]) {
	Dungeon dungeon(Dungeons::BSP,80,40,3); // (Dungeons &_type,const int & _width,const int & _height, const int & _depth)
	bool s = dungeon.generateDungeon();
	int ch = 0;
	int x,y;
	do{
		x = std::rand() % 80;
		y = std::rand() % 40;
	}while(dungeon(x,y)!=ROOM);
	dungeon.setPlayer(x,y);
	dungeon.print();

	
    while(1){
        ch = getch();
		if(ch!=0){
			if (ch==UP) dungeon.movePlayer(0,-1);
			if (ch==DOWN) dungeon.movePlayer(0,1);
			if (ch==RIGHT) dungeon.movePlayer(1,0);
			if (ch==LEFT) dungeon.movePlayer(-1,0);
			dungeon.print();
		}
        if(ch == 3){
            return 0;
        }
	}
	return 0;
}
