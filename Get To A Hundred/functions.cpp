#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include "functions.h"
using namespace std;

//Return 1 if the input is proper, 0 otherwise
int inputCheck(string in) {
	if (in.compare("q") == 0) return -1;
	else if (in.length() != 1 && in.length() != 2) return 0;
	for (int i = 0; i < in.length(); i++) {
		if (!isdigit(in[i])) return 0;
	}
	int n = stoi(in);
	if (n < 1 || n > 10) return 0;
	return n;
}

//Return the next possible winning number that the computer needs to reach
int getWinningNum(int tTemp, int* winningNums) {
	for (int i = 0; i < 11; i++) {
		if (tTemp <= winningNums[i]) return winningNums[i];
	}
}

//print the following text
void printText(int mode string diff, int randnum) {
	cout << "Let's play a game. Enter 'q' to quit"
		<< "\n========================================================================"
		<< "\nThe rules are simple: "
		<< "\n1. The starting number will always be 0"
		<< "\n2. Enter a number between 1-10 that will be added to the starting number"
		<< "\n3. We will enter our own number one at a time"
		<< "\n4. Player who reaches to 100 first wins"
		<< "\n5. Player who exceeds beyond 100 loses"
		<< "\n========================================================================" << endl;
	if (mode == 1) {
		cout << "Mode: Singleplayer" << endl;
		cout << "Level of difficulty: " << diff << endl;
		cout << "\nA random number has been rolled. If that number is 1, you go first, else the computer goes first."
			<< "\nRandom number: " << randnum << endl;
	}
	else {
		cout << "Mode: Multiplayer" << endl;
		cout << "\nA random number has been rolled. If that number is 1, player 1 goes first, else player 2 goes first."
			<< "\nRandom number: " << randnum << endl;
	}
}

//Return 1 if the player want to play again, 0 otherwise
int playAgain() {
	string userInput = "";
	while (userInput.compare("y") != 0 || userInput.compare("n") != 0 || userInput.compare("q") != 0) {
		cout << "Play again? (y/n): ";
		getline(cin, userInput);
		userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end()); //remove every occurance of space
		userInput.erase(remove(userInput.begin(), userInput.end(), '\t'), userInput.end()); //remove every occurance of tab

		if (userInput.length() == 1) {
			if (tolower(userInput[0]) == 'y') return 1;
			else if (tolower(userInput[0]) == 'n' || tolower(userInput[0]) == 'q') return 0;
		}
		system("CLS");
	}
}

//Return 1 if any of the players have won the game, 2 if any of the players went beyond 100, 0 otherwise
int winCheck(int tTemp) {
	if (tTemp == 100) return 1;
	else if (tTemp > 100) return 2;
	return 0;
}
