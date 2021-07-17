#ifndef LINUX_GAME_INPUT_IMPL_CPP
#define LINUX_GAME_INPUT_IMPL_CPP

#include <DungeonGame/utill/Input.hpp>
namespace LinuxGame{
	/* Initialize new terminal i/o settings */
	void initTermios(int echo) 
	{
		if(init) return;
		init = true;
		tcgetattr(STDIN_FILENO, &old); /* grab old terminal i/o settings */
		newp = old; /* make new settings same as old settings */
		newp.c_lflag &= ~ICANON; /* disable buffered i/o */
		newp.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
		tcsetattr(STDIN_FILENO, TCSANOW, &newp); /* use these new terminal i/o settings now */
	}

	/* Restore old terminal i/o settings */
	void resetTermios(void) 
	{
		tcsetattr(0, TCSANOW, &old);
	}

	/* Read 1 character - echo defines echo mode */
	char getch_(int echo) 
	{
		char ch=0;
		initTermios(echo);
		if(!kbhit()) return ch;
		ch = getchar();
		while(!(ch == UP || ch==DOWN || ch==LEFT || ch==RIGHT)){
			ch = getchar();
		}
		// resetTermios();
		return ch;
	}

	/* Read 1 character without echo */
	char getch(void) 
	{
		char ch = getch_(0);
		return ch;
	}

	/* Read 1 character with echo */
	char getche(void) 
	{
		char ch = getch_(1);
		return ch;
	}

	void gotoxy(const int &x, const int & y)
	{
		printf("%c[%d;%df",0x1B,y,x);
	}
	
	int kbhit (void)
	{
		  struct timeval tv;
		  fd_set rdfs;

		  tv.tv_sec = 0;
		  tv.tv_usec = 0;

		  FD_ZERO(&rdfs);
		  FD_SET (STDIN_FILENO, &rdfs);

		  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
		  return FD_ISSET(STDIN_FILENO, &rdfs);

	}
	

}




#endif