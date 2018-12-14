#include <cassert>       // For assert
#include"Command.h"


Command::Command()
{
	mCommand = "";
	mValue = "";
}  // end default constructor


Command::Command(string inCommand, string inValue, int inLineNumber)
{
	mCommand = inCommand;
	mValue = inValue;
	mLineNumber = inLineNumber;
}


void Command::setCommand(char inCommand)
{
	mCommand = inCommand;
}



string Command::getCommand() const
{
	return mCommand;
}


void Command::setValue(string inValue)
{
	mValue = inValue;
}

string Command::getValue() const
{
	return mValue;
}

void Command::setLine(int inLineNumber) {
	mLineNumber = inLineNumber;
}

int Command::getLine()const {
	return mLineNumber;
}