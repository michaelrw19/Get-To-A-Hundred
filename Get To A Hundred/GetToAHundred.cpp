#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include "List.h"
#include "Difficulty.h"
#include "Functions.h"
#include "GetToAHundred.h"
using namespace std;

GetToAHundred::GetToAHundred(int mode) {
	this->mode = mode;

	this->wNPtr = winningNums;
	this->player1 = new List(50);
	this->player2 = new List(50); //or computer
	this->total = new List(100);

	this->randnum = (rand() % 2) + 1;
	this->turn = randnum;
	this->win = 0;
}

GetToAHundred::GetToAHundred(int mode, int lvl) {
	this->diff = new Difficulty(lvl);	
	this->mode = mode;

	this->wNPtr = winningNums;
	this->player1 = new List(50);
	this->player2 = new List(50); //or computer
	this->total = new List(100);

	this->randnum = (rand() % 2) + 1;
	this->turn = randnum;
	this->win = 0;
}

//Return 1 if the input from the player is proper (numbers 1-10), 0 otherwise
int GetToAHundred::inputCheck(string in) {
	if (in.compare("q") == 0) return -1;
	else if (in.length() != 1 && in.length() != 2) return 0;
	for (int i = 0; i < in.length(); i++) {
		if (!isdigit(in[i])) return 0;
	}
	int n = stoi(in);
	if (n < 1 || n > 10) return 0;
	return n;
}

//Return 1 if any of the players have won the game, 2 if any of the players went beyond 100, 0 otherwise
int GetToAHundred::winCheck() {
	if (total->getLastNum() == 100) return 1;
	else if (total->getLastNum() > 100) return 2;
	return 0;
}

int GetToAHundred::getPlayerNumber() {
	string userInput;
	int number = 0;
	while (number == 0) {
		system("CLS");
		printText();
		printRecord();

		if(mode == 1) cout << "\nYour turn, enter a number between 1 - 10: ";
		else if (mode == 2 && turn == 1) cout << "\nPlayer 1's turn, enter a number between 1 - 10: ";
		else if (mode == 2 && turn == 2) cout << "\nPlayer 2's turn, enter a number between 1 - 10: ";

		getline(cin, userInput);
		userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end()); //remove every occurance of space
		userInput.erase(remove(userInput.begin(), userInput.end(), '\t'), userInput.end()); //remove every occurance of tab

		number = inputCheck(userInput);
		if (number == -1) {
			deleteMemory();
			exit(0);
		}
	}
	return number;
}

void GetToAHundred::addPlayer1Record(int p1Temp) {
	player1->addNum(p1Temp);
}
void GetToAHundred::addPlayer2Record(int p2Temp) {
	player2->addNum(p2Temp);
}
void GetToAHundred::addTotalRecord(int tTemp) {
	total->addNum(tTemp);
}

void GetToAHundred::changeTurn() {
	if (turn == 1) turn = 2;
	else turn = 1;
}

int GetToAHundred::getTurn() {
	return turn;
}

int GetToAHundred::getComputerNumber(int tTemp, int pTemp) {
	return diff->getNumber(tTemp, getWinningNum(tTemp), pTemp);
}

//Return the next possible winning number that the computer needs to reach
int GetToAHundred::getWinningNum(int tTemp) {
	for (int i = 0; i < 11; i++) {
		if (tTemp <= this->wNPtr[i]) return this->wNPtr[i];
	}
}

//print the following text
void GetToAHundred::printText() {
	cout << "====== Get to a Hundred ======" << endl;

	cout << "\nLet's play a game. Enter 'q' to quit"
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
		cout << "Level of difficulty: " << diff->getType() << endl;
		if (diff->getType().compare("Moderate") == 0) {
			cout << "Type: " << diff->getMedType() << endl;
		}
		cout << "\nA random number has been rolled. If that number is 1, you go first, else the computer goes first."
			<< "\nRandom number: " << randnum << endl;
	}
	else {
		cout << "Mode: Multiplayer" << endl;
		cout << "\nA random number has been rolled. If that number is 1, player 1 goes first, else player 2 goes first."
			<< "\nRandom number: " << randnum << endl;
	}
}

//print the numbers that the players have entered
void GetToAHundred::printRecord() {
	//player 2 = computer (in singleplayer mode)
	string name;
	if (mode == 1) name = "Computer";
	else name = "Player 2";

	int stage = 1;

	if (randnum == 1) {
		for (int i = 0; i < total->getLength(); i++) {
			if (i % 2 == 0) cout << "\n============== " << "Stage " << stage << " ==============" << endl;

			if (i % 2 == 0) cout << "Player 1 enters " << player1->getNumAt(i / 2) << endl;
			else cout << name << " enters " << player2->getNumAt(i / 2) << endl;
			cout << "Starting number: " << total->getNumAt(i) << endl;

			if (i % 2 != 0) {
				cout << "=====================================" << endl;
				stage++;
			}
		}
	}
	else {
		for (int i = 0; i < total->getLength(); i++) {
			if (i % 2 == 0) cout << "\n============== " << "Stage " << stage << " ==============" << endl;

			if (i % 2 == 0) cout << name << " enters " << player2->getNumAt(i / 2) << endl;
			else cout << "Player 1 enters " << player1->getNumAt(i / 2) << endl;
			cout << "Starting number: " << total->getNumAt(i) << endl;

			if (i % 2 != 0) {
				cout << "=====================================" << endl;
				stage++;
			}
		}
	}
}

void GetToAHundred::printWinningInfo() {
	if (mode == 1) {
		if (winCheck() == 1) {
			if (getTurn() == 1) cout << "\nComputer reaches 100. COMPUTER WINS!" << endl; //turns = 1, last input must be from computer
			else cout << "\nPlayer 1 reaches 100. PLAYER 1 WINS!" << endl; //turns = 2, last input must be from player
		}
		else cout << "\nPlayer 1 exceeds 100, player 1 lose. COMPUTER WINS!" << endl;
	}
	else {
		if (winCheck() == 1) {
			if (getTurn() == 1) cout << "\nPlayer 2 reaches 100. PLAYER 2 WINS!" << endl; //turns = 1, last input must be from p2
			else cout << "\nPlayer 1 reaches 100. PLAYER 1 WINS!" << endl; //turns = 2, last input must be from p1
		}
		else {
			if (getTurn() == 1) cout << "\nPlayer 2 exceeds 100, player 2 lose. PLAYER 1 WINS!" << endl;
			else cout << "\nPlayer 1 exceeds 100, player 1 lose. PLAYER 2 WINS!" << endl;
		}
	}
}

//Return 1 if the player want to play again, 0 otherwise
int GetToAHundred::playAgain() {
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

//delete all dynamic allocated memory 
//for single player mode
void GetToAHundred::deleteMemory() {
	total->deleteNums();
	player1->deleteNums();
	player2->deleteNums(); //or computer

	if(mode == 1) delete(diff);
}