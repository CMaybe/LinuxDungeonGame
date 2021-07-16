#include <DungeonGame/Dungeon/Dungeon.hpp>

using namespace LinuxDungeon;


Dungeon::Dungeon(const Dungeons &_type,const int & _width,const int & _height, const int & _depth){
	std::srand(std::time(nullptr));
	this->width  = _width;  
	this->height = _height; 
	this->depth  = _depth; 
	this->type   = _type;
	this->dungeon.resize(_height);
	for(int i = 0;i<_height;i++){
		this->dungeon[i].resize(_width);
	}
}

void Dungeon::init(int tile){
	for(int i = 0;i<this->dungeon.size(); i++){
		for(int j = 0;j<this->dungeon[0].size(); j++){
			this->dungeon[i][j]=WALL;
		}
	}
	
	for(int i = 1;i<this->dungeon.size()-1;i++){
		for(int j = 1;j<this->dungeon[0].size()-1;j++){
			this->dungeon[i][j]=tile;
		}
	}
}

void Dungeon::print(){
	std::string output="";
	
	for(int i = 0;i<this->dungeon.size();i++){
		for(int j = 0;j<this->dungeon[0].size();j++){
			switch(this->dungeon[i][j]){
				case NONE:
					output+=" *";
					break;
				case ROOM:
					output+="  ";
					break;
				case TUNNEL:
					output+=" `";
					break;
				case WALL:
					output+=" .";
					break;
				case LINE:
					output+=" +";
					break;
				case PLAYER:
					output+="●";
			}
		}
		output+='\n';
	}
	std::cout<<output;
}

Edge Dungeon::BSP(int x1,int y1,int x2, int y2, bool flag, int cnt){
	if(cnt==depth){
		x1 += std::rand() % 3 +2;
		if(x1<1) x1=1;
		if(x1>this->dungeon[0].size()-1) x1=this->dungeon[0].size()-1;
		y1 += std::rand() % 3 + 2;
		if(y1<1) y1=1;
		if(y1>this->dungeon.size()-1) y1=this->dungeon.size()-1;
		x2 -= std::rand() % 3  + 2;
		if(x2<1) x2=1;
		if(x2>this->dungeon[0].size()-1) x2=this->dungeon[0].size()-1;
		y2 -= std::rand() % 3 + 2;
		if(y2<1) y2=1;
		if(y2>this->dungeon.size()-1) y2=this->dungeon.size()-1;
		for(int i=y1;i<y2;i++){
			for(int j=x1;j<x2;j++){
				this->dungeon[i][j]=ROOM;
			}
		}
		return Edge{x1,y1,x2-1,y2-1};
	}
	
	int t_x1 = 0;
	int t_x2 = 0;
	int t_y1 = 0;
	int t_y2 = 0;
	if(flag == H){
		int t = (x2+x1)/2 + (std::rand() % 4 - 2);
		for(int i=y1;i<=y2;i++){
			this->dungeon[i][t]=LINE;
		}
		Edge p1 = BSP(x1,y1,t,y2,W,cnt+1); // left
		Edge p2 = BSP(t,y1,x2,y2,W,cnt+1); // right
		
		t_x1 = p1.x2;
		t_x2 = p2.x1;
		t_y1 = std::min(p1.y1,p2.y1);
		t_y2 = std::max(p1.y2,p2.y2);
		int up = 0,down = 0;
		do{
			up = std::rand() % (t_y2-t_y1) + t_y1;
			down = std::rand() % (t_y2-t_y1) + t_y1;
		}while(this->dungeon[up][t_x1]!=ROOM || this->dungeon[down][t_x2]!=ROOM);
		bool pflag=true;
		for(int i = t_x1+1;i<t_x2;i++){
			if(this->dungeon[up][i]==TUNNEL || this->dungeon[up][i]==LINE){
				this->dungeon[up][i]=TUNNEL;
				int dir = up < down ? 1 : -1;
				int j = 0;
				for(j = up;j!=down;j+=dir){
					this->dungeon[j][i]=TUNNEL;
				}
				this->dungeon[j][i]=TUNNEL;
				pflag = false;
				continue;
			}
			if(pflag){
				if(this->dungeon[up][i]==ROOM) break;
				this->dungeon[up][i]=TUNNEL;
			}
			else{
				if(this->dungeon[down][i]==ROOM) break;
				this->dungeon[down][i]=TUNNEL;
			}
		}
		return Edge{p1.x1,std::min(p1.y1,p2.y1),p2.x2,std::max(p1.y2,p2.y2)};

		
	}
	else if(flag == W){
		int t = (y2+y1)/2 + (std::rand() % 4 - 2);
		for(int i=x1;i<=x2;i++){
			this->dungeon[t][i]=LINE;
		}
		Edge p1 = BSP(x1,y1,x2,t,H,cnt+1); // up
		Edge p2 = BSP(x1,t,x2,y2,H,cnt+1); // down
		
		
		t_x1 = std::min(p1.x1,p2.x1);
		t_x2 = std::max(p1.x2,p2.x2);
		t_y1 = p1.y2;
		t_y2 = p2.y1;
		
		int left = 0,right = 0;
		do{
			left = std::rand() % (t_x2-t_x1) + t_x1;
			right = std::rand() % (t_x2-t_x1) + t_x1;
		}while(this->dungeon[t_y1][left]!=ROOM || this->dungeon[t_y2][right]!=ROOM);
		bool pflag=true;
		for(int i = t_y1+1;i<t_y2;i++){
			if(this->dungeon[i][left]==TUNNEL || this->dungeon[i][left]==LINE){
				this->dungeon[i][left]=TUNNEL;
				int dir = left < right ? 1 : -1;
				int j = 0;
				for(j = left;j!=right;j+=dir){
					this->dungeon[i][j]=TUNNEL;
				}
				this->dungeon[i][j]=TUNNEL;
				pflag = false;
				continue;
			}
			if(pflag){
				if(this->dungeon[i][left]==ROOM) break;
				this->dungeon[i][left]=TUNNEL;
			}
			else{
				if(this->dungeon[i][left]==ROOM) break;
				this->dungeon[i][right]=TUNNEL;
			} 
		}
		return Edge{std::min(p1.x1,p2.x1),p1.y1,std::max(p1.x2,p2.x2),p2.y2};
	}
	return Edge{t_x1,t_y1,t_x2,t_y2};
}

void Dungeon::pre2Real(){
	for(int i = 0;i<this->dungeon.size();i++){
		for(int j = 0;j<this->dungeon.size();j++){
			if(this->dungeon[i][j]==PRE_WALL) this->dungeon[i][j] = WALL;
			if(this->dungeon[i][j]==PRE_ROOM) this->dungeon[i][j] = ROOM;
		}
	}
}

void Dungeon::Cellular_Automata(const int wall_ratio,const int wall_effected,const int room_effected, int count){
	int wall_cnt = (this->dungeon[0].size()-2)*(this->dungeon.size()-2)*wall_ratio/100;
	int cnt = 0;
	while(cnt++<wall_cnt){
		int x = std::rand() % (this->dungeon[0].size()-1) + 1;
		int y = std::rand() % (this->dungeon.size()-1) + 1;
		if(this->dungeon[y][x]!=WALL) this->dungeon[y][x]=WALL;
		else cnt--;
	}
	while(count--){
		for(int i = 1;i<this->dungeon.size()-1;i++){
			for(int j = 1;j<=this->dungeon[0].size()-1;j++){
				int wc = 0; // wall count;
				if(this->dungeon[i+1][j-1]==WALL) wc++;
				if(this->dungeon[i][j-1]==WALL) wc++;
				if(this->dungeon[i-1][j-1]==WALL) wc++;
				if(this->dungeon[i+1][j+1]==WALL) wc++;
				if(this->dungeon[i][j+1]==WALL) wc++;
				if(this->dungeon[i-1][j+1]==WALL) wc++;
				if(this->dungeon[i+1][j]==WALL) wc++;
				if(this->dungeon[i-1][j]==WALL) wc++;
				if(wc >= wall_effected){
					for(int k=i-1;k<=i+1;k++){
						for(int w=j-1;w<=j+1;w++){
							this->dungeon[k][w]=PRE_WALL;
						}
					}
				}
			}
		}
		for(int i = 1;i<this->dungeon.size()-1;i++){
			for(int j = 1;j<=this->dungeon[0].size()-1;j++){
				int rc = 0; // room count;
				if(this->dungeon[i+1][j-1]==ROOM) rc++;
				if(this->dungeon[i][j-1]==ROOM) rc++;
				if(this->dungeon[i-1][j-1]==ROOM) rc++;
				if(this->dungeon[i+1][j+1]==ROOM) rc++;
				if(this->dungeon[i][j+1]==ROOM) rc++;
				if(this->dungeon[i-1][j+1]==ROOM) rc++;
				if(this->dungeon[i+1][j]==ROOM) rc++;
				if(this->dungeon[i-1][j]==ROOM) rc++;
				if(rc >= room_effected){
					for(int k=i-1;k<=i+1;k++){
						for(int w=j-1;w<=j+1;w++){
							this->dungeon[k][w]=PRE_ROOM;
						}
					}
				}
			}
		}
		pre2Real();
	}
	
	return;
}

const std::vector<std::vector<int>> & Dungeon::getDungeon() const {
	return this->dungeon;
}

bool Dungeon::generateDungeon(){
	try{
		switch(this->type){
			case Dungeons::BSP:
				BSP(1,1,this->width-1,this->height-1,H,0);
				break;
				
			case Dungeons::Celluar_Automata:
				Cellular_Automata(20,4,7,7);
				break;
		}
	}catch(int e){
       return false;
    }
	return true;
}


int& Dungeon::operator()(const int& row, const int& col) {
	return this->dungeon[row][col];
}

const int& Dungeon::operator()(const int& row, const int& col) const {
	return this->dungeon[row][col];
}

int Dungeon::getWidth() const {
	return this->width;
}
int Dungeon::getHeight() const {
	return this->height;
}

