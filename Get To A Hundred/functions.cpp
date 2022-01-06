#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include "functions.h"
using namespace std;

int inputCheck(string in, char code) {
	if (in.compare("q") == 0) return -1;
	else if (in.length() != 1 && in.length() != 2) return 0;
	for (int i = 0; i < in.length(); i++) {
		if (!isdigit(in[i])) return 0;
	}
	int n = stoi(in);
	if (code == 'd' && (n < 1 || n > 3)) return 0;
	if (code == 'i' && (n < 1 || n > 10)) return 0;
	return n;
}

int getWinningNum(int tTemp, int* winningNums) {
	for (int i = 0; i < 11; i++) {
		if (tTemp <= winningNums[i]) return winningNums[i];
	}
}

void printText(string diff, int randnum) {
	cout << "Let's play a game. Enter 'q' to quit"
		<< "\n========================================================================"
		<< "\nThe rules are simple: "
		<< "\n1. The starting number will always be 0"
		<< "\n2. Enter a number between 1-10 that will be added to the starting number"
		<< "\n3. We will enter our own number one at a time"
		<< "\n4. Player who reaches to 100 first wins"
		<< "\n4. Player who exceeds beyond 100 loses"
		<< "\n========================================================================" << endl;
	cout << "Level of difficulty: " << diff << endl;
	cout << "\nA random number has been rolled. If that number is 1 you go first, else the computer goes first."
		<< "\nRandom number: " << randnum << endl;
}

/*
void printRecord(List* total, List* computer, List* player, int randnum) {
	int stage = 1;
	if (randnum) {
		for (int i = 0; i < total->getLength(); i++) {
			if (i % 2 == 0) cout << "\n============== " << stage << " ==============" << endl;

			if (i % 2 == 0) cout << "Player enters " << player->getNumAt(i / 2) << endl;
			else cout << "Computer enters " << computer->getNumAt(i / 2) << endl;
			cout << "Starting number: " << total->getNumAt(i) << endl;

			if (i % 2 != 0) {
				cout << "===============================" << endl;
				stage++;
			}
		}
	}
	else {
		for (int i = 0; i < total->getLength(); i++) {
			if (i % 2 == 0) cout << "\n============== " << stage << " ==============" << endl;

			if (i % 2 == 0) cout << "Computer enters " << computer->getNumAt(i / 2) << endl;
			else cout << "Player enters " << player->getNumAt(i / 2) << endl;
			cout << "Starting number: " << total->getNumAt(i) << endl;

			if (i % 2 != 0) {
				cout << "===============================" << endl;
				stage++;
			}
		}
	}
}

void deleteClasses(List* total, List* computer, List* player, Difficulty* diff) {
	total->deleteNums();
	computer->deleteNums();
	player->deleteNums();
	delete(diff);
}
*/

int playAgain() {
	string in = "";
	while (in.compare("y") != 0 || in.compare("n") != 0 || in.compare("q") != 0) {
		cout << "Play again? (y/n): ";
		getline(cin, in);
		in.erase(remove(in.begin(), in.end(), ' '), in.end()); //remove every occurance of space
		in.erase(remove(in.begin(), in.end(), '\t'), in.end()); //remove every occurance of tab

		if (in.length() == 1) {
			if (tolower(in[0]) == 'y') return 1;
			else if (tolower(in[0]) == 'n' || tolower(in[0]) == 'q') exit(0);
		}
		system("CLS");
	}
}

int winCheck(int tTemp) {
	if (tTemp == 100) return 1;
	else if (tTemp > 100) return 2;
	return 0;
}