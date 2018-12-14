#pragma once
#include"LinkedStack.h"
#include"LinkedList.h"
#include"Command.h"
#include<string>
#include "BinarySearchTree.h"

class Editor
{
public:
	Editor();
	void displayLines(); //const
	void readFile(string);
	int getCurrentPosition() const;
	void setCurrentPositon(int);
	int getCurrentLine() const;
	void setCurrentLine(int);
	void processCommand(char ch[2]);
	void replaceLine(string, int);
	int getCount() const;

private:
	LinkedList<string> myList;
	/*LinkedList<char>myChar;*/
	LinkedStack<Command> undoStack;
	int mCurrentPosition;
	int mCurrentLine;
	string myLine;
	BinarySearchTree<string> myKeywordsBST;
	int mLineCount = 0; //To keep track of the # of lines inserted on our list
	string charString;

};


