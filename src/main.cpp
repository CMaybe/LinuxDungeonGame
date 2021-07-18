#include <DungeonGame/Dungeon/Dungeon.hpp>
#include <DungeonGame/utill/Input.hpp>
#include <DungeonGame/utill/Output.hpp>

#include <iostream>
#include <cstdlib>
#include <vector>



using namespace LinuxGame;



int main(int argc, char* argv[]) {
	Dungeon dungeon(Dungeons::BSP,42,42,2); // (Dungeons &_type,const int & _width,const int & _height, const int & _depth)
	bool s = dungeon.generateDungeon();
	OutputBuffer output((dungeon.getWidth() * 2 + 2)* dungeon.getHeight(),'B');
	int ch = 0;
	int x,y;
	do{
		x = std::rand() % dungeon.getWidth();
		y = std::rand() % dungeon.getHeight();
	}while(dungeon(x,y)!=ROOM);
	dungeon.setPlayer(x,y);
	// dungeon.print();
	for(int i = 0;i<dungeon.getHeight();i++){
		output(i*(dungeon.getWidth()*2+2) + dungeon.getWidth())= ' ';
		output(i*(dungeon.getWidth()*2+2) + dungeon.getWidth()*2+1)= '\n';	
	}

	
    while(1){
        ch = getch();
		if(ch!=0){
			if (ch==UP) dungeon.movePlayer(0,-1);
			if (ch==DOWN) dungeon.movePlayer(0,1);
			if (ch==RIGHT) dungeon.movePlayer(1,0);
			if (ch==LEFT) dungeon.movePlayer(-1,0);
			std::string buffer =  dungeon.getStringMap(); // 41
			Point player = dungeon.getPlayerPosition();

			for(int i = player.y - 6,py=0;i <= player.y+6;i++,py+=3){
				for(int j = player.x - 6,px=0;j <= player.x+6;j++,px+=3){
					if(i<0 || j<0 || j>=dungeon.getWidth() || i>=dungeon.getHeight()) continue;
					for(int t=0;t<3;t++){
						for(int k=0;k<3;k++){
							output((py+t)*(dungeon.getWidth()*2+2)+(px+k)) = buffer[i*(dungeon.getWidth()+1)+j]; // x,y
						}
					}
					output(i*(dungeon.getWidth()*2+2)+(j + dungeon.getWidth()+1)) = buffer[i*(dungeon.getWidth()+1)+j]; // x,y
				}	
			}
			output.print();

		}
        if(ch == 3){
            return 0;
        }
	}
	return 0;
}
