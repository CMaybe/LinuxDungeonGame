#ifndef LINUX_GAME_INPUT_HPP
#define LINUX_GAME_INPUT_HPP

#include <termios.h>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#define UP 		65
#define DOWN 	66
#define RIGHT 	67
#define LEFT 	68



namespace LinuxGame{

	static struct termios old, newp;

	/* Initialize new terminal i/o settings */
	void initTermios(int echo);

	/* Restore old terminal i/o settings */
	void resetTermios(void);

	/* Read 1 character - echo defines echo mode */
	char getch_(int echo);

	/* Read 1 character without echo */
	char getch(void);

	/* Read 1 character with echo */
	char getche(void);
	
	void gotoxy(int x,int y);
	
	int kbhit (void);
}


#endif