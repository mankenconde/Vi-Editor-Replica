#pragma once
#include"LinkedStack.h"
#include"LinkedList.h"
#include"Command.h"
#include<string>

class Editor
{
public:
	Editor();
	void displayLines() const;
	void readFile(string);
	int getCurrentPosition() const;
	void setCurrentPositon(int);
	int getCurrentLine() const;
	void setCurrentLine(int);
	void processCommand(char ch[2]);
	void replaceLine(string, int);
	//void replaceChar(char, int);

private:
	LinkedList<string> myList;
	/*LinkedList<char>myChar;*/
	LinkedStack<Command> undoStack;
	int mCurrentPosition;
	int mCurrentLine;
	string myLine;
};


