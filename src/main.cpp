#include <DungeonGame/Dungeon/Dungeon.hpp>
#include <DungeonGame/utill/Input.hpp>
#include <DungeonGame/utill/Output.hpp>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>



using namespace LinuxGame;



int main(int argc, char* argv[]) {
	Dungeon dungeon(Dungeons::BSP,77,40,3); // (Dungeons &_type,const int & _width,const int & _height, const int & _depth)
	bool s = dungeon.generateDungeon();
	OutputBuffer output((dungeon.getWidth() * 2 + 2)* dungeon.getHeight(),'B');
	int ch = 0;
	int x,y;
	const int sight_x=10,sight_y=5,zoom=3;
	do{
		x = std::rand() % dungeon.getWidth();
		y = std::rand() % dungeon.getHeight();
	}while(dungeon(x,y)!=ROOM);
	dungeon.setPlayer(x,y);
	Point player = dungeon.getPlayerPosition();

	for(int i = 0;i<dungeon.getHeight();i++){
		output(i*(dungeon.getWidth()*2+2) + dungeon.getWidth())= ' ';
		output(i*(dungeon.getWidth()*2+2) + dungeon.getWidth()*2+1)= '\n';	
	}
	
	std::string buffer =  dungeon.getStringMap(); // 41
	for(int i = player.y - sight_y,py=0;i <= player.y+sight_y;i++,py+=zoom){
		for(int j = player.x - sight_x,px=0;j <= player.x+sight_x;j++,px+=zoom){
			if(i<0 || j<0 || j>=dungeon.getWidth() || i>=dungeon.getHeight()) continue;
			for(int t=0;t<zoom;t++){
				for(int k=0;k<zoom;k++){
					output((py+t)*(dungeon.getWidth()*2+2)+(px+k)) = buffer[i*(dungeon.getWidth()+1)+j]; // player sight
				}
			}	
			output(i*(dungeon.getWidth()*2+2)+(j + dungeon.getWidth()+1)) = buffer[i*(dungeon.getWidth()+1)+j]; // map
		}	
	}
	output.print();

	
    while(1){
        ch = getch();
		if(ch!=0){
			if (ch==UP) dungeon.movePlayer(0,-1);
			if (ch==DOWN) dungeon.movePlayer(0,1);
			if (ch==RIGHT) dungeon.movePlayer(1,0);
			if (ch==LEFT) dungeon.movePlayer(-1,0);
			player = dungeon.getPlayerPosition();
			buffer =  dungeon.getStringMap(); // 41
			// bool move = true;
			// if((buffer[std::max(player.y-sight_y,0)*(dungeon.getWidth()+1)+std::max(player.x-sight_x,0)] == ROOM
			// 	&& buffer[std::min(player.y+sight_y,dungeon.getHeight()-1)*(dungeon.getWidth()+1)+std::min(player.x+sight_x,dungeon.getWidth()-1)] == ROOM)
			//   	){
			// 	move = false;
			// }
			// if(buffer[player.y*(dungeon.getWidth()+1)+player.x]==TUNNEL) move = true;
			for(int i = player.y - sight_y,py=0;i <= player.y+sight_y;i++,py+=zoom){
				for(int j = player.x - sight_x,px=0;j <= player.x+sight_x;j++,px+=zoom){
					if(i<0 || j<0 || j>=dungeon.getWidth() || i>=dungeon.getHeight()) continue;
					for(int t=0;t<zoom;t++){
						for(int k=0;k<zoom;k++){
							output((py+t)*(dungeon.getWidth()*2+2)+(px+k)) = buffer[i*(dungeon.getWidth()+1)+j]; // player sight
						}
					}	
					output(i*(dungeon.getWidth()*2+2)+(j + dungeon.getWidth()+1)) = buffer[i*(dungeon.getWidth()+1)+j]; // map
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
