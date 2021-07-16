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



namespace LinuxDungeon{
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

	
	class Dungeon{
		private:
			int width,height,depth;
			Dungeons type;
			std::vector<std::vector<int>> dungeon;
			void init(int tile);
			void pre2Real();

		public:
			Dungeon(const LinuxDungeon::Dungeons &_type,const int & _width = 50,const int & _height = 50, const int & _depth = 5);
		
			virtual ~Dungeon(){};
			const std::vector<std::vector<int>> & getDungeon() const;
			bool generateDungeon();
			void print();
			LinuxDungeon::Edge BSP(int x1,int y1,int x2, int y2, bool flag, int cnt);
			void Cellular_Automata(const int wall_ratio,const int wall_effected,const int room_effected, int count);
		
			int& operator()(const int& row, const int& col);
			const int& operator()(const int& row, const int& col) const;
		
			int getWidth() const;
			int getHeight() const;
		
		
			

	};
	
}
