#ifndef LINUX_GAME_DUNGEON_HPP
#define LINUX_GAME_DUNGEON_HPP


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#define H true
#define W false

#define PLAYER		7
#define PRE_WALL	6
#define PRE_ROOM	5
#define LINE		4
#define WALL 		3
#define TUNNEL 		2
#define ROOM		1
#define NONE 		0



namespace LinuxGame{
	typedef struct EDGE{
		int x1;
		int y1;
		int x2;
		int y2;
	}Edge;

	enum class Dungeons{
		BSP,
		Celluar_Automata
	};
	
	typedef struct POINT{
		int x;
		int y;
	}Point;

	
	class Dungeon{
		private:
			int width,height,depth,playerX,playerY,preX,preY, preBlock;
			int wall_ratio, wall_effected, room_effected, count;
		
			Dungeons type;
			std::vector<std::vector<int>> dungeon;
			void init(int tile);
			void pre2Real();

		public:
			Dungeon(const LinuxGame::Dungeons &_type,const int & _width,const int & _height, const int & _depth);
			Dungeon(const LinuxGame::Dungeons &_type,const int & _width ,const int & _height ,const int _wall_ratio, const int _wall_effected, const int _room_effected, int _count);
		
			virtual ~Dungeon(){};
			const std::vector<std::vector<int>> & getDungeon() const;
			std::string getStringMap();
			bool generateDungeon();
			void print();
			void setPlayer(const int &x, const int & y);
			void movePlayer(const int &dx, const int & dy);
			LinuxGame::Edge BSP(int x1,int y1,int x2, int y2, bool flag, int cnt);
			void Cellular_Automata();
		
			int& operator()(const int& x, const int& y);
			const int& operator()(const int& x, const int& y) const;
		
			int getWidth() const;
			int getHeight() const;
		
			LinuxGame::Point getPlayerPosition() const;
			

	};
	
}

#endif