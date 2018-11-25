#include"Editor.h"
#include"LinkedList.h"
#include<fstream>
#include<string>
#include <conio.h>

#define ESC 27 //for esc button in Insert function

//#include "LinkedStack.h"

using namespace std;

Editor::Editor()
{
	mCurrentPosition = 0;
	mCurrentLine = 1;
}

void Editor::readFile(string fileName)
{
	fstream inData;
	string line;
	char letter;

	inData.open(fileName);
	if (!inData)
		cout << "Error opening file" << endl;

	for (int i = 1; !inData.eof(); i++)
	{
		getline(inData, line);
		myList.insert(i, line);

		/*for (int j = 1; j < line.length(); j++) {
			myChar.insert(j, line[j - 1]);
		}*/

	}
}

void Editor::displayLines() const
{
	int i, j;
	for (i = 1; i < myList.getLength() + 1; i++)
	{
		if (i == mCurrentLine)
		{
			cout << "^" << myList.getEntry(i) << endl;
			for (int j = 1; j < mCurrentPosition; j++)
			{
				cout << " ";
			}
			cout << " ^" << endl;
		}
		else
			cout << " " << myList.getEntry(i) << endl;
	}

}

int Editor::getCurrentPosition() const
{
	return mCurrentPosition;
}

void Editor::setCurrentPositon(int inCurrentPosition)
{
	mCurrentPosition = inCurrentPosition;
}

int Editor::getCurrentLine() const
{
	return mCurrentLine;
}

void Editor::setCurrentLine(int inCurrentLine)
{
	mCurrentLine = inCurrentLine;
}

void Editor::processCommand(char ch[2])
{
	// j: page down
	// k: Page up
	// l: right
	// h: left
	// R: replace Line
	// r: replace Char NOT WORKING (may not be necessary)
	// u: undo

	string newLine;
	Command myCommand;
	/*char newChar;*/

	switch (ch[0])
	{
		

	case 'j':
		myLine = myList.getEntry(mCurrentLine);
		if (mCurrentLine == myList.getLength())
			mCurrentLine = mCurrentLine;
		else {
			mCurrentLine++;
			if (myList.getEntry(mCurrentLine).length() < mCurrentPosition) {
				mCurrentPosition = myList.getEntry(mCurrentLine).length();
			}

		}

		break;
	case 'k':


		myLine = myList.getEntry(mCurrentLine);
		if (mCurrentLine == 1)
			mCurrentLine = mCurrentLine;
		else {
			mCurrentLine--;
			if (myList.getEntry(mCurrentLine).length() < mCurrentPosition) {
				mCurrentPosition = myList.getEntry(mCurrentLine).length();
			}

		}

		break;
	case 'l':

		myLine = myList.getEntry(mCurrentLine);//mCurrentPosition + 1);

		if (mCurrentPosition == myLine.length())
			mCurrentPosition = mCurrentPosition;
		else
			mCurrentPosition++;
		break;
	case 'h':
		myLine = myList.getEntry(mCurrentLine);
		if (mCurrentPosition == 0)
			mCurrentPosition = mCurrentPosition;
		else
			mCurrentPosition--;
		break;


	case'R':
		myLine = myList.getEntry(mCurrentLine);
		//string newLine;
		cin >> newLine;
		replaceLine(newLine, mCurrentLine);

		myCommand.setCommand(ch[0]);
		myCommand.setValue(myLine);
		undoStack.push(myCommand);

		break;


	//case 'r':
	//	myLine = myList.getEntry(mCurrentLine);
	//	//char newChar;
	//	cin >> newChar;
	//	replaceChar(newChar, mCurrentPosition);


	case'u':

		if(!undoStack.isEmpty()){

			if(undoStack.peek().getCommand()[0]=='d'){
		myList.insert(undoStack.peek().getLine(),undoStack.peek().getValue());
		undoStack.pop();
			}

			else if (undoStack.peek().getCommand()[0] == 'I') {
				myList.remove(undoStack.peek().getLine());
				undoStack.pop();
			}
		}
		
		break;

	case'd':
		if (ch[1] == 'd') {
			
			myCommand.setValue(myList.getEntry(mCurrentLine));
			myCommand.setCommand(ch[0]+ch[1]);
			myCommand.setLine(mCurrentLine);
			undoStack.push(myCommand);
			/*undoStack.push(myCommand.getValue());
			undoStack.push(myCommand.getLine());*/

			myList.remove(mCurrentLine);

			break;
		}

	case 'I':
		
		string input;
		int insert_line_count = 1;

		getline(cin, input);
		input[0] = _getch(); //Necessary in order to be able to get the first character
							//of the input and store it in input[0] in order to be able to use
							// it in the condition of the while loop

		if (input[0] != ESC) {


			myList.insert(mCurrentLine, input);
		getline(cin, input);

		input[0] = _getch(); //Necessary in order to be able to get the first character
							//of the input and store it in input[0] in order to be able to use
							// it in the condition of the while loop
		}

		else {
			myList.insert(mCurrentLine, input);
			//myCommand.setValue(myList.getEntry(mCurrentLine));
			myCommand.setCommand(ch[0]);
			myCommand.setLine(mCurrentLine);
			undoStack.push(myCommand);
			break;
		}
		
	}
}

void Editor::replaceLine(string sentence, int position) {

	myList.replace(position, sentence);
}

//void Editor::replaceChar(char letter, int position) {
//	myChar.replace(position, letter);
//}