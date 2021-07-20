#ifndef LINUX_GAME_OUTPUT_IMPL_CPP
#define LINUX_GAME_OUTPUT_IMPL_CPP

#include <DungeonGame/utill/Output.hpp>
namespace LinuxGame{

	void gotoxy(const int &x, const int & y)
	{
		printf("%c[%d;%df",0x1B,y,x); // 사실 함수가 아닌 명령어를 통한 작동입니다. \033[L;Cf 가 Lows,Columns으로 좌표를 이동시키는 명령어입니다. 
	}
	
	OutputBuffer::OutputBuffer(){}
	
	OutputBuffer::OutputBuffer(std::string s){
		buffer = s;
		size = s.length();
	}
	
	OutputBuffer::OutputBuffer(int _size, char ch){
		resize(_size,ch);		
	}
	

	OutputBuffer::~OutputBuffer(){}
	
	void OutputBuffer::print()
	{
		gotoxy(0,0);
		std::cout<<buffer << std::endl;
	}
	
	void OutputBuffer::resize(int _size, char ch){
		buffer = "";
		size = _size;
		for(int i = 0;i<size;i++){
			buffer+=ch;
		}
	}
	
	void OutputBuffer::clear(){
		buffer="";
		size = 0;
	}
	
	
	// 문자열과 연산입니다.
	OutputBuffer& OutputBuffer::operator=(const std::string& rhs){
		this->buffer = rhs;
		this->size = buffer.length();
		return *this;
	}
	
	OutputBuffer& OutputBuffer::operator+=(const std::string& rhs){
		this->buffer += rhs;
		return *this;
	}
	
	const std::string & OutputBuffer::getBuffer() const{
		return this->buffer;
	}

	
	// l - value 입니다.
	char& OutputBuffer::operator()(const int& idx) {
		return this->buffer[idx];
	}

	// r - value 입니다.
	const char& OutputBuffer::operator()(const int& idx) const {
		return this->buffer[idx];
	}
	


}




#endif