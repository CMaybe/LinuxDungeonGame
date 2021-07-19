#ifndef LINUX_GAME_OUTPUT_HPP
#define LINUX_GAME_OUTPUT_HPP

#include <iostream>
#include <string>
#include <vector>

namespace LinuxGame{
	void gotoxy(const int &x, const int & y);

	class OutputBuffer{
		private:
			int size;
			std::string buffer;

		public:
			OutputBuffer();
			OutputBuffer(std::string s);
			OutputBuffer(int _size,char ch = '\0');

			virtual ~OutputBuffer();
			void print();
			void resize(int size, char ch = ' ');
			void clear();
			const std::string& getBuffer() const;
		
			OutputBuffer& operator+=(const std::string& rhs);
			OutputBuffer& operator=(const std::string& rhs);

			char& operator()(const int& idx);
			const char& operator()(const int& idx) const;
		
	};

}

#endif