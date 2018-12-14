#include"Editor.h"
#include"LinkedList.h"
#include<fstream>
#include<string>
#include <conio.h>
#include <sstream>
#include <Windows.h>
#include <vector>
#include <iterator> //Need for "istream_iterator"
#include <cstring> //Needed to use the "erase" function for x command

#define ESC 27 //for esc button in Insert function

//#include "LinkedStack.h"

using namespace std;

// be sure to include the headers, <sstream> and <windows.h>
// and change contains in the BST implementation to !=

void goToXY(int column, int line) {

	COORD coord;

	coord.X = column;

	coord.Y = line;

	SetConsoleCursorPosition(

		GetStdHandle(STD_OUTPUT_HANDLE),

		coord);

}

void colorText(int value) {

	COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, value);

}

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

	ifstream inFile;
	inFile.open("keyword.txt");

	while (!inFile.eof()) {
		string words;
		inFile >> words;
		myKeywordsBST.add(words);


	}

	inData.open(fileName);
	if (!inData)
		cout << "Error opening file" << endl;

	for (int i = 1; !inData.eof(); i++)
	{
		getline(inData, line);
		myList.insert(i, line);
		mLineCount++;



		
		/*for (int j = 1; j < line.length(); j++) {
			myChar.insert(j, line[j - 1]);
		}*/

	}

	
}

void Editor::displayLines() //const
{
	/*int i, j;
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
	}*/

	string myLine;

	int i, j;

	for (i = 1; i<myList.getLength() + 1; i++) {

		myLine = myList.getEntry(i);
		istringstream streamWords{myLine};

		vector<string> words{
			istream_iterator<string>(streamWords), istream_iterator<string>()
		};

		bool isKeyword;
		for (string currentWord : words) {

			isKeyword = myKeywordsBST.contains(currentWord);

			if (isKeyword)

				colorText(FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | 0X80);  //blue

			else
				//colorText(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | 0X80);

				colorText(0XF0);

			cout << currentWord << " ";
		}
		cout << endl;
	}
	goToXY(mCurrentPosition, mCurrentLine - 1);

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
	// x: delete char
	// #+command = example "4J" would move 4 lines down *EXTRA CREDIT*

	string newLine;
	Command myCommand;
	/*char newChar;*/
	char inputChecker;

	string input; //Local Variable for Inser command
	int insert_line_count = 1; //Local Variable for Inser command

	int charToNum = 0;
	int prefixAction = 0;

	if (ch[0] > '0' && ch[0] <= '10') {
		charToNum = ch[0] - '0';
		/*if (ch[1] == 'j') {
			prefixAction=mCurrentL charToNum;
		}*/
	}




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

		if (!undoStack.isEmpty()) {

			if (undoStack.peek().getCommand()[0] == 'd') {
				myList.insert(undoStack.peek().getLine(), undoStack.peek().getValue());
				mLineCount++;
				undoStack.pop();
				
			}

			else if (undoStack.peek().getCommand()[0] == 'I') {
				myList.remove(undoStack.peek().getLine());
				mLineCount--;
				undoStack.pop();
			}

			else if (undoStack.peek().getCommand()[0] == 'x') {
				myList.replace(undoStack.peek().getLine(), undoStack.peek().getValue());
				undoStack.pop();
			}
		}

		break;

	case'd':
		if (ch[1] == 'd') {

			myCommand.setValue(myList.getEntry(mCurrentLine));
			myCommand.setCommand(ch[0]);
			myCommand.setLine(mCurrentLine);
			undoStack.push(myCommand);
			/*undoStack.push(myCommand.getValue());
			undoStack.push(myCommand.getLine());*/

			myList.remove(mCurrentLine);

			mLineCount--;	
		}

		break;

	case 'I':



		getline(cin, input);
		inputChecker = _getch();

		/* input[0] does not work. but when we replaced it with a new char that we created called inputchecker
		it works with that one instead */
		//input[0] = _getch(); //Necessary in order to be able to get the first character
							//of the input and store it in input[0] in order to be able to use
							// it in the condition of the while loop

		if (inputChecker != ESC) {


			myList.insert(mCurrentLine, input);
			getline(cin, input);

			inputChecker = _getch(); //Necessary in order to be able to get the first character
								//of the input and store it in input[0] in order to be able to use
								// it in the condition of the while loop

			mLineCount++;

		}

		else {
			myList.insert(mCurrentLine, input);
			//myCommand.setValue(myList.getEntry(mCurrentLine));
			myCommand.setCommand(ch[0]);
			myCommand.setLine(mCurrentLine);
			undoStack.push(myCommand);

			mLineCount++;

		}

		break;

	case 'x':
		charString = myList.getEntry(mCurrentLine);

		//if(charString[mCurrentPosition]!=' '){
		myCommand.setValue(myList.getEntry(mCurrentLine));
		myCommand.setCommand(ch[0]);
		myCommand.setLine(mCurrentLine);
		undoStack.push(myCommand);


		charString.erase(charString.begin() + mCurrentPosition);
		myList.replace(mCurrentLine, charString);
		//}


	}
}

void Editor::replaceLine(string sentence, int position) {

	myList.replace(position, sentence);
}


int Editor::getCount() const {
	return mLineCount;
}