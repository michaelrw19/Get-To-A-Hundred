#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include "list.h"
#include "Difficulty.h"
#include "functions.h"
using namespace std;

void printRecord(List* total, List* computer, List* player, int randnum);
void deleteClasses(List* total, List* computer, List* player, Difficulty* diff);

int main() {

	int winningNums[11] = { 1, 12, 23, 34, 45, 56, 67, 78, 89, 100 };
	int* wNPtr = winningNums;

	while (1) {
		string in;
		int win = 0;

		system("CLS");
		//=================== Game explanation and choosing difficulty ===================//
		cout << "Let's play a game. Enter 'q' to quit"
			<< "\n========================================================================"
			<< "\nThe rules are simple: "
			<< "\n1. The starting number will always be 0"
			<< "\n2. Enter a number between 1-10 that will be added to the starting number"
			<< "\n3. We will enter our own number one at a time"
			<< "\n4. Player who reaches to 100 first wins"
			<< "\n4. Player who exceeds beyond 100 loses"
			<< "\n========================================================================" << endl;
		cout << "Level of Difficulties:" << "\n(1) Easy" << "\n(2) Moderate" << "\n(3) Hard" << endl;

		int lvl = 0;

		while (lvl == 0) {
			cout << "Choose the level of difficulty (Enter the number): ";
			getline(cin, in);
			in.erase(remove(in.begin(), in.end(), ' '), in.end()); //remove every occurance of space
			in.erase(remove(in.begin(), in.end(), '\t'), in.end()); //remove every occurance of tab

			lvl = inputCheck(in, 'd'); //'d' for difficulty input, 'i' for number input when playing
			if (lvl == -1) exit(0);
		}

		Difficulty* diff = new Difficulty(lvl - 1); //Generate difficulty

	    List* computer = new List(50);
		List* player = new List(50);
		List* total = new List(100);

		int cTemp = 0;
		int pTemp = 0;
		int tTemp = 0;

		int randnum = rand() % 2;
			//If randnum = 1, player plays first
			//If randnum = 0, computer plays first
		int turns = randnum;
		//===============================================================================//


		//=================== Beginning of Game ===================//
		while (win == 0) {
			system("CLS");
			printText(diff->getType(), randnum);
			printRecord(total, computer, player, randnum);

			//Computer's turn
			if (turns == 0) { 
				cTemp = diff->getNumber(tTemp, getWinningNum(tTemp, wNPtr), pTemp); 
				pTemp = 0; //Reset to allow the while loop to run again
				
				cout << "\nComputer's turn, computer enters: ";
				Sleep(((rand() % 6) + 1) * 500); //Variatons of pause duration 500 ms - 3000 ms (multiple of 500)
				cout << cTemp;
				Sleep(250);

				//Inputing data
				tTemp += cTemp;
				computer->addNum(cTemp);
				total->addNum(tTemp);

				//Change turns
				turns = 1; 
			}
			//Player's turn
			else { 

				while (pTemp == 0) {
					system("CLS");
					printText(diff->getType(), randnum);
					printRecord(total, computer, player, randnum);

					cout << "\nYour turn, enter a number between 1 - 10: ";
					getline(cin, in);
					in.erase(remove(in.begin(), in.end(), ' '), in.end()); //remove every occurance of space
					in.erase(remove(in.begin(), in.end(), '\t'), in.end()); //remove every occurance of tab

					pTemp = inputCheck(in, 'i');
					if (pTemp == -1) {
						deleteClasses(total, computer, player, diff);
						exit(0);
					}
				}

				//Inputing data
				tTemp += pTemp;
				player->addNum(pTemp);
				total->addNum(tTemp);
				//pTemp = 0; //Moved to computer's turn (line 73)
				// If the above line isnt moved to line 73, then for algorithm 7 the computer will always return 0 instead of the player's number
				turns = 0;
			}
			win = winCheck(tTemp);
		}
		//If someone wins
		system("CLS");
		printText(diff->getType(), randnum);
		printRecord(total, computer, player, randnum);
		deleteClasses(total, computer, player, diff);

		if (win == 1) {
			if (turns) cout << "\nComputer reaches 100. COMPUTER 1 WINS!" << endl; //turns = 0, last input must be from player 1
			else cout << "\nPlayer 1 reaches 100. PLAYER 1 WINS!" << endl; //turns = 1, last input must be from computer
		}
		else {
			if (!turns) cout << "\nPlayer 1 exceeds 100, player 1 lose. COMPUTER WINS!" << endl;
		}

		if (!playAgain()) exit(0);
		//====================================================//
	}
}

//print all of the numbers that the player and the computer have entered
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

//delete all dynamic allocated memory 
void deleteClasses(List* total, List* computer, List* player, Difficulty* diff) {
	total->deleteNums();
	computer->deleteNums();
	player->deleteNums();
	delete(diff);
}
