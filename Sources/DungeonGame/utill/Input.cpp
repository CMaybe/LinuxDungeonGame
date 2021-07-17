#ifndef LINUX_GAME_INPUT_IMPL_CPP
#define LINUX_GAME_INPUT_IMPL_CPP

#include <DungeonGame/utill/Input.hpp>
namespace LinuxGame{
	/* Initialize new terminal i/o settings */
	void initTermios(int echo) 
	{
		tcgetattr(0, &old); /* grab old terminal i/o settings */
		newp = old; /* make new settings same as old settings */
		newp.c_lflag &= ~ICANON; /* disable buffered i/o */
		newp.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
		tcsetattr(0, TCSANOW, &newp); /* use these new terminal i/o settings now */
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
		ch = getchar();
		resetTermios();
		return ch;
	}

	/* Read 1 character without echo */
	char getch(void) 
	{
		char ch = getch_(0);
		if(ch==27){getch_(0);ch=getch_(0); }
		return ch;
	}

	/* Read 1 character with echo */
	char getche(void) 
	{
		char ch = getch_(1);
		if(ch==27){getch_(1);ch=getch_(1); }
		return ch;
	}

	void gotoxy(int x,int y)
	{
		printf("%c[%d;%df",0x1B,y,x);
	}
}




#endif