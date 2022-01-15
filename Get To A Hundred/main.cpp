#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include "list.h"
#include "difficulty.h"
#include "functions.h"
using namespace std;

//Update: Multiplayer Mode added

void playSinglePlayer();
void playMultiplayer();

void printRecord(int mode, List* total, List* computer, List* player, int randnum);
void deleteMemory(List* total, List* player1, List* computer, Difficulty* diff);
void deleteMemory(List* total, List* player1, List* computer);

int main() {
	// 1 => Singleplayer
	// 2 => Multiplayer
	string userInput;
	int mode = 0;

	while (1) {
		while (mode == 0) {
			system("CLS");
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
			cout << "Modes:" << "\n(1) Singleplayer" << "\n(2) Multiplayer" << endl;
			cout << "Select mode: ";
			getline(cin, userInput);
			userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end()); //remove every occurance of space
			userInput.erase(remove(userInput.begin(), userInput.end(), '\t'), userInput.end()); //remove every occurance of tab

			//Input check
			if (userInput.compare("1") == 0) mode = 1;
			else if (userInput.compare("2") == 0) mode = 2;
			else if (userInput.compare("q") == 0) exit(0);
			else mode = 0;
		}

		if (mode == 1) playSinglePlayer();
		else playMultiplayer();
	}
}

void playSinglePlayer() {
	int winningNums[11] = { 1, 12, 23, 34, 45, 56, 67, 78, 89, 100 };
	int* wNPtr = winningNums;

	while (1) {
		string userInput;
		int win = 0;
		int lvl = 0;

		while (lvl == 0) {
			system("CLS");
			cout << "====== Get to a Hundred ======" << endl;
			//=================== Game explanation and choosing difficulty ===================//
			cout << "\nLet's play a game. Enter 'q' to quit"
				<< "\n========================================================================"
				<< "\nThe rules are simple: "
				<< "\n1. The starting number will always be 0"
				<< "\n2. Enter a number between 1-10 that will be added to the starting number"
				<< "\n3. We will enter our own number one at a time"
				<< "\n4. Player who reaches to 100 first wins"
				<< "\n4. Player who exceeds beyond 100 loses"
				<< "\n========================================================================" << endl;
			cout << "Level of Difficulties:" << "\n(1) Easy" << "\n(2) Moderate" << "\n(3) Hard" << endl;
			cout << "Choose the level of difficulty: ";
			getline(cin, userInput);
			userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end()); //remove every occurance of space
			userInput.erase(remove(userInput.begin(), userInput.end(), '\t'), userInput.end()); //remove every occurance of tab

			//Input check
			if (userInput.compare("1") == 0) lvl = 1;
			else if (userInput.compare("2") == 0) lvl = 2;
			else if (userInput.compare("3") == 0) lvl = 3;
			else if (userInput.compare("q") == 0) exit(0);
			else lvl = 0;
		} 

		Difficulty* diff = new Difficulty(lvl); //Generate difficulty

		List* computer = new List(50);
		List* player = new List(50);
		List* total = new List(100);

		//Temporary variables to store the player's input, computer's number, and current / starting number
		int cTemp = 0;
		int pTemp = 0;
		int tTemp = 0;

		//If randnum = 1, player plays first
		//If randnum = 2, computer plays first
		int randnum = (rand() % 2) + 1;
		int turns = randnum;
		//===============================================================================//

		//=================== Beginning of Game ===================//
		while (win == 0) {
			system("CLS");
			printText(1, diff->getType(), randnum);
			printRecord(1, total, player, computer, randnum);

			//Player's turn
			if (turns == 1) {
				while (pTemp == 0) {
					system("CLS");
					printText(1, diff->getType(), randnum);
					printRecord(1, total, player, computer, randnum);

					cout << "\nYour turn, enter a number between 1 - 10: ";
					getline(cin, userInput);
					userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end()); //remove every occurance of space
					userInput.erase(remove(userInput.begin(), userInput.end(), '\t'), userInput.end()); //remove every occurance of tab

					pTemp = inputCheck(userInput);
					if (pTemp == -1) {
						deleteMemory(total, player, computer, diff);
						exit(0);
					}
				}
				//Inputing data
				tTemp += pTemp;
				player->addNum(pTemp);
				total->addNum(tTemp);

				turns = 2;
			}
			//Computer's turn
			else {
				//Get the number to win the game
				cTemp = diff->getNumber(tTemp, getWinningNum(tTemp, wNPtr), pTemp);
				pTemp = 0;

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
			win = winCheck(tTemp);
		}
		//If someone wins
		system("CLS");
		printText(1, diff->getType(), randnum);
		printRecord(1, total, player, computer, randnum);
		deleteMemory(total, player, computer, diff);
		if (win == 1) {
			if (turns == 1) cout << "\nComputer reaches 100. COMPUTER WINS!" << endl; //turns = 1, last input must be from computer
			else cout << "\nPlayer 1 reaches 100. PLAYER 1 WINS!" << endl; //turns = 2, last input must be from player
		}
		else {
			if (turns == 1) cout << "\nPlayer 1 exceeds 100, player 1 lose. COMPUTER WINS!" << endl;
		}

		if (!playAgain()) exit(0);
		//====================================================//
	}
}

void playMultiplayer() {
	int winningNums[11] = { 1, 12, 23, 34, 45, 56, 67, 78, 89, 100 };
	int* wNPtr = winningNums;

	while (1) {
		string userInput;
		int win = 0;

		List* player1 = new List(50);
		List* player2 = new List(50);
		List* total = new List(100);

		int p1Temp = 0;
		int p2Temp = 0;
		int tTemp = 0;

		//If randnum = 1, player 1 plays first
		//If randnum = 2, player 2 plays first
		int randnum = (rand() % 2) + 1;
		int turns = randnum;

		//=================== Beginning of Game ===================//
		while (win == 0) {
			system("CLS");
			printText(2, "", randnum);
			printRecord(2, total, player1, player2, randnum);

			//Player 1's turn
			if (turns == 1) {
				while (p1Temp == 0) {
					system("CLS");
					printText(2, "", randnum);
					printRecord(2, total, player1, player2, randnum);

					cout << "\nPlayer 1's turn, enter a number between 1 - 10: ";
					getline(cin, userInput);
					userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end()); //remove every occurance of space
					userInput.erase(remove(userInput.begin(), userInput.end(), '\t'), userInput.end()); //remove every occurance of tab

					p1Temp = inputCheck(userInput);
					if (p1Temp == -1) {
						deleteMemory(total, player1, player2);
						exit(0);
					}
				}
				//Inputing data
				tTemp += p1Temp;
				player1->addNum(p1Temp);
				total->addNum(tTemp);
				p1Temp = 0; //Reset to allow the while loop to run again

				//Change turns
				turns = 2;
			}

			//Player 2's turn
			else {
				while (p2Temp == 0) {
					system("CLS");
					printText(2, "", randnum);
					printRecord(2, total, player1, player2, randnum);

					cout << "\nPlayer 2's turn, enter a number between 1 - 10: ";
					getline(cin, userInput);
					userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end()); //remove every occurance of space
					userInput.erase(remove(userInput.begin(), userInput.end(), '\t'), userInput.end()); //remove every occurance of tab

					p2Temp = inputCheck(userInput);
					if (p2Temp == -1) {
						deleteMemory(total, player1, player2);
						exit(0);
					}
				}

				//Inputing data
				tTemp += p2Temp;
				player2->addNum(p2Temp);
				total->addNum(tTemp);
				p2Temp = 0; //Reset to allow the while loop to run again

				//Change turns
				turns = 1;
			}
			win = winCheck(tTemp);
		}
		//If someone wins
		system("CLS");
		printText(2, "", randnum);
		printRecord(2, total, player1, player2, randnum);
		deleteMemory(total, player1, player2);

		if (win == 1) {
			if (turns == 2) cout << "\nPlayer 1 reaches 100 first. PLAYER 1 WINS!" << endl; //turns = 2, last input must be from player 1
			else cout << "\nPlayer 2 reaches 100 first. PLAYER 2 WINS!" << endl; //turns = 1, last input must be from player 2
		}
		else {
			if (turns == 2) cout << "\nPlayer 1 exceeds 100, player 1 lose. PLAYER 2 WINS!" << endl;
			else cout << "\nPlayer 2 exceeds 100, player 2 lose. PLAYER 1 WINS!" << endl;
		}

		if (!playAgain()) exit(0);
	}
}

//print the numbers that the players have entered
void printRecord(int mode, List* total, List* player1, List* player2, int randnum) {
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

//delete all dynamic allocated memory 
//for single player mode
void deleteMemory(List* total, List* player1, List* computer, Difficulty* diff) {
	total->deleteNums();
	player1->deleteNums();
	computer->deleteNums();
	delete(diff);
}

//for single player mode
void deleteMemory(List* total, List* player1, List* player2) {
	total->deleteNums();
	player1->deleteNums();
	player2->deleteNums();
}
