#ifndef LINUX_GAME_INPUT_IMPL_CPP
#define LINUX_GAME_INPUT_IMPL_CPP

#include <DungeonGame/utill/Input.hpp>
namespace LinuxGame{
	/* Initialize new terminal i/o settings */
	void initTermios(void) 
	{
		tcgetattr(STDIN_FILENO, &setting); // Terminal 기본입력의 현재 설정값을 setting 저장합니다.
		setting.c_lflag &= ~ICANON; // ICANON은 입력을 개행문자로 받을 결정하는 bit mask입니다. 저희는 개행문자로 받으면 안되기 대문에 ~을 넣어줍니다. 
		setting.c_lflag &= ~ECHO; // ECHO는 말그대로 입력한 문자를 보여줄지 결정하는 bit mask 입니다 마찬가지로 없어야 합니다 
		tcsetattr(STDIN_FILENO, TCSANOW, &setting); // 만들어둔 설정을 TCSANOW을 통해 즉시 적용합니다  
		init = true;  // 초기화 했다는 flag입니다.
	}
	

	char getch(void) 
	{
		char ch=0;
		if(init==false) initTermios(); // 초기화하지 않았다면 초기화를 실행시킵니다.
		
		if(!kbhit()) return ch; // 키보드 입력이 없다면 0(NULL)을 return합니다.
		ch = getchar(); // 입력이 있었다면 입력값을 받아옵니다.
		printf("%c\n",ch);
		if(ch!=27) return ch;
		while(!(ch == UP || ch==DOWN || ch==LEFT || ch==RIGHT)){
			ch = getchar(); // 쓸모없는 값을 지우고 우리가 원하는 값만 받아옵니다.
		}
		return ch;
	}

	int kbhit (void)
	{
		struct timeval tv;
		fd_set rdfs; // 파일 기술자의 대한 값을 넣을 구조체 입니다.

		// 입력받은 값을 즉시 처리하기 위해 시간을 0으로 설정해줍니다.
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		
		
		FD_ZERO(&rdfs); // rdfs를 초기화 시킵니다.
		FD_SET (STDIN_FILENO, &rdfs); // rdfs에 표준 입력(keyboard input)에 대한 값을 넣습니다.

		select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv); 
		/* STDIN_FILENO+1 인 이유는 첫번째 인자가 Index가 아닌 갯수이기 때문입니다.
			STDIN_FILENO는 내부적으로 0이기 때문에 1개의 값을 처리하기 위해 +1를 해줍니다.
			두번째 인자는 읽을 데이터가 있는지 감시하는 변수입니다.원래는 배열형식이지만 저희는 한개라 값을 ref로 전달합니다.
			마지막 변수는 time out 값입니다. 저희는 변화하느 값을 즉시 확인하기 위해 0을 미리 넣어두었습니다.
		*/
		return FD_ISSET(STDIN_FILENO, &rdfs); // rdfs안에 STDIN_FILENO값이 설정되었는 확인합니다. 즉 키보드 인풋이 있었는지 확인합니다.

	}
	

}




#endif