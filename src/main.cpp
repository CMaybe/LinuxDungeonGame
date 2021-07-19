#include <DungeonGame/Dungeon/Dungeon.hpp>
#include <DungeonGame/utill/Input.hpp>
#include <DungeonGame/utill/Output.hpp>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>


using namespace LinuxGame;



int main(int argc, char* argv[]) {
	Dungeon dungeon(Dungeons::BSP,77,40,2); // (Dungeons &_type,const int & _width,const int & _height, const int & _depth)
	bool s = dungeon.generateDungeon();
	OutputBuffer output((dungeon.getWidth() * 2 + 2)* dungeon.getHeight(),'B');
	int ch = 0;
	int x,y;
	int px =0,py = 0; // padding 
	const int sight_x=10,sight_y=5,zoom=3;
	do{
		x = std::rand() % dungeon.getWidth();
		y = std::rand() % dungeon.getHeight();
	}while(dungeon(x,y)!=ROOM);
	std::string ori = dungeon.getStringMap();
	dungeon.setPlayer(x,y);
	Point player = dungeon.getPlayerPosition();

	for(int i = 0;i<dungeon.getHeight();i++){
		output(i*(dungeon.getWidth()*2+2) + dungeon.getWidth())= ' ';
		output(i*(dungeon.getWidth()*2+2) + dungeon.getWidth()*2+1)= '\n';	
	}
	
	std::string buffer =  dungeon.getStringMap(); // (width + 1) * height 
	for(int i = player.y - sight_y,my=0;i <= player.y+sight_y;i++,my+=zoom){
		for(int j = player.x - sight_x,mx=0;j <= player.x+sight_x;j++,mx+=zoom){
			if(i<0 || j<0 || j>=dungeon.getWidth() || i>=dungeon.getHeight()) continue;
			for(int t=0;t<zoom;t++){
				for(int k=0;k<zoom;k++){
					output((my+t)*(dungeon.getWidth()*2+2)+(mx+k)) = buffer[i*(dungeon.getWidth()+1)+j]; // player sight
				}
			}	
			output(i*(dungeon.getWidth()*2+2)+(j + dungeon.getWidth()+1)) = buffer[i*(dungeon.getWidth()+1)+j]; // map
		}	
	}
	output.print();

	int fix = 0; // fix map
    while(1){
        ch = getch();
		if(ch!=0){
			if (ch==UP) dungeon.movePlayer(0,-1);
			if (ch==DOWN) dungeon.movePlayer(0,1);
			if (ch==RIGHT) dungeon.movePlayer(1,0);
			if (ch==LEFT) dungeon.movePlayer(-1,0);
			buffer =  dungeon.getStringMap(); // 41
			player = dungeon.getPlayerPosition();
			
			
			int lx=0,rx=0,uy=0,dy=0;
			while (buffer[(player.y + uy)*(dungeon.getWidth()+1)+player.x] == ' ' && player.y - uy > std::max(player.y - sight_y - py,0)) uy--;
			while (buffer[(player.y + dy)*(dungeon.getWidth()+1)+player.x] == ' ' && player.y - dy < std::min(player.y + sight_y - py,dungeon.getHeight()-1)) dy++;
			while (buffer[player.y*(dungeon.getWidth()+1)+player.x + rx] == ' '	  && player.x + rx < std::min(player.x + sight_x - px,dungeon.getWidth()-1)) rx++;
			while (buffer[player.y*(dungeon.getWidth()+1)+player.x + lx] == ' '   && player.x - lx > std::max(player.x - sight_x - px,0)) lx--;
			
			if(ori[player.y*(dungeon.getWidth()+1)+player.x]=='`') fix = 0;
			else fix = 1;
			if(fix==1){
				if (ch==UP		&& player.y - uy == std::max(player.y - sight_y - py,0))	py-=1;
				if (ch==DOWN	&& player.y - dy == std::min(player.y + sight_y - py,dungeon.getHeight()-1))	py+=1;
				if (ch==RIGHT	&& player.x + rx == std::min(player.x + sight_x - px,dungeon.getWidth()-1))	px+=1;
				if (ch==LEFT	&& player.x - lx == std::max(player.x - sight_x - px,0))	px-=1;
			}
			for(int i = player.y - sight_y - py,my=0;i <= player.y+sight_y - py;i++,my+=zoom){
				for(int j = player.x - sight_x - px,mx=0;j <= player.x+sight_x - px;j++,mx+=zoom){
					if(i<0 || j<0 || j>=dungeon.getWidth() || i>=dungeon.getHeight()) continue;
					for(int t=0;t<zoom;t++){
						for(int k=0;k<zoom;k++){
							output((my+t)*(dungeon.getWidth()*2+2)+(mx+k)) = buffer[i*(dungeon.getWidth()+1)+j]; // player sight
						}
					}	
					output(i*(dungeon.getWidth()*2+2)+(j + dungeon.getWidth()+1)) = buffer[i*(dungeon.getWidth()+1)+j]; // map
				}	
			}
			output.print();
			std::cout<<"\n1 : "<<static_cast<int>(buffer[std::max(player.y-sight_y - py,0)*(dungeon.getWidth()+1)+std::max(player.x-sight_x - px,0)]);
			std::cout<<"\n2 : "<<static_cast<int>(buffer[std::min(player.y+sight_y+py,dungeon.getHeight()-1)*(dungeon.getWidth()+1)+std::min(player.x+sight_x+px,dungeon.getWidth()-1)]);
			std::cout<<'\n'<<ori[player.y*(dungeon.getWidth()+1)+player.x];
			std::cout<<'\n'<<fix<<'\n';

		}
        if(ch == 3){
            return 0;
        }
	}
	return 0;
}
