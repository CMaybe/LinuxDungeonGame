#include <iostream>
#include <DungeonGame/Dungeon/Generator.hpp>
#include <DungeonGame/utill/Input.hpp>
#include <cstdlib>
#include <vector>



using namespace Dungeon;



int main(int argc, char* argv[]) {
	Generator generator(Dungeons::BSP,80,40,3); // (Dungeons &_type,const int & _width,const int & _height, const int & _depth)
	bool s = generator.generateDungeon();
	std::vector<std::vector<int>> dungeon = generator.getDungeon();
	dungeon[34][43]=0;
	
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
