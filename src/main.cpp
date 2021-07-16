#include <iostream>
#include <DungeonGame/Dungeon/Dungeon.hpp>
#include <DungeonGame/utill/Input.hpp>
#include <cstdlib>
#include <vector>



using namespace LinuxDungeon;



int main(int argc, char* argv[]) {
	Dungeon dungeon(Dungeons::BSP,80,40,3); // (Dungeons &_type,const int & _width,const int & _height, const int & _depth)
	bool s = dungeon.generateDungeon();
	dungeon.print();
	int ch = 0;
	
 
    while(1){
        ch = getch();
		if(ch==27){getch();ch=getch(); }
        if(ch != 0){
            printf("%d\n\r",ch);
        }
        if(ch == 3){
            return 0;
        }         
	}
	return 0;
}
