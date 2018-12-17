#include "Editor.h"
#include <conio.h>

using namespace std;

int main() {


	Editor myEditor;

	myEditor.readFile("Text.txt");
	/*myEditor.readFile("keyword.txt");*/

	myEditor.displayLines();

	char ch[2];
		ch[0] = _getche();
		//ch[1] = _getche();

		

	do {

		myEditor.processCommand(ch);

		system("cls"); //Clears the screen before displaying the lines again

		myEditor.displayLines();

		ch[0] = _getch();

		if (ch[0] == 'd') {
			ch[1] = _getch();
		}

		else if (ch[0] - '0' >= 1 && ch[0] - '0' <= 10) {
			ch[1] = _getch();
		}



	} while (ch[0] != 'q');

	myEditor.setCurrentLine(myEditor.getCount());

	system("cls"); //Clears the screen before displaying the lines again

	myEditor.displayLines();

	cout << "\n You have EXITED the program." << endl;

	//Editor myEditor;

	//string newSentence;
	//string fullSentence;
	//int position;

	//myEditor.readFile("Text.txt");
	//myEditor.displayLines();

	//cout << "\n\n Please enter the line number you would like to replace" << endl;
	//cin >> position;

	//cout << "\n Please enter the sentence you would like to replace it with" << endl;

	//cin.ignore(); //cin.ignore() is necessary because without it, the program does not wait
	//				//for an input due to the use of getline() function.
	//getline(cin,newSentence);

	//myEditor.replaceLine(newSentence, position);
	//cout << "-------------------------" << endl;
	//myEditor.displayLines();


	system("pause");
	return 0;
}