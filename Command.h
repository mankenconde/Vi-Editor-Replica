//#pragma once
#ifndef COMMAND_
#define COMMAND_
#include <string>
#include<iostream>
using namespace std;

class Command
{
public:
	Command();
	Command(string, string, int);
	void setCommand(char);
	string getCommand() const;
	void setValue(string);
	string getValue() const;
	void setLine(int);
	int getLine()const;

private:
	string mCommand;
	string mValue;
	int mLineNumber;
	//int position;
};

#endif