#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include "list.h"
#include "difficulty.h"
#include "GetToAHundred.h"
using namespace std;

//Update: All functions in functions.h are moved to GetToAHundred.h, including printRecord and deleteMemory function.

int playSinglePlayer(int mode);
int playMultiplayer(int mode);

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
		if (mode == 1) {
			if (playSinglePlayer(mode) == 0) exit(0);
		}
		else {
			if (playMultiplayer(mode) == 0) exit(0);
		}
		mode = 0;
	}
}

void playSinglePlayer() {
	while (1) {
		string userInput;
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
				<< "\n5. Player who exceeds beyond 100 loses"
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
		//Temporary variables to store the player's input, computer's number, and current / starting number
		int cTemp = 0;
		int pTemp = 0;
		int tTemp = 0;

		GetToAHundred game(mode, lvl);
		//===============================================================================//

		//=================== Beginning of Game ===================//
		while (game.winCheck() == 0) {
			system("CLS");
			game.printText();
			game.printRecord();
			
			//Player's turn
			if (game.getTurn() == 1) {
				pTemp = game.getPlayerNumber();
				//Inputing data
				tTemp += pTemp;
				game.addPlayer1Record(pTemp);
				game.addTotalRecord(tTemp);
				//Change turn
				game.changeTurn();
			}
			//Computer's turn
			else {
				//Get the number to win the game
				cTemp = cTemp = game.getComputerNumber(tTemp, pTemp);

				cout << "\nComputer's turn, computer enters: ";
				Sleep(((rand() % 6) + 1) * 500); //Variatons of pause duration 500 ms - 3000 ms (multiple of 500)
				cout << cTemp;
				Sleep(250);

				//Inputing data
				tTemp += cTemp;
				game.addPlayer2Record(cTemp);
				game.addTotalRecord(tTemp);
				//Change turns
				game.changeTurn();
			}
		}
		system("CLS");
		game.printText();
		game.printRecord();
		game.printWinningInfo();

		game.deleteMemory();
		return game.playAgain();
		//====================================================//
	}
}

int playMultiplayer(int mode) {
	while (1) {
		string userInput;
		//Temporary variables to store the player 1's input, player 2's input, and starting number
		int p1Temp = 0;
		int p2Temp = 0;
		int tTemp = 0;

		GetToAHundred game(mode);
		
		//===============================================================================//

		//=================== Beginning of Game ===================//
		while (game.winCheck() == 0) {
			system("CLS");
			game.printText();
			game.printRecord();

			//Player 1's turn
			if (game.getTurn() == 1) {
				p1Temp = game.getPlayerNumber();
				//Inputing data
				tTemp += p1Temp;
				game.addPlayer1Record(p1Temp);
				game.addTotalRecord(tTemp);
				
				//Change turns
				game.changeTurn();
			}
			//Player 2's turn
			else {
				p2Temp = game.getPlayerNumber();
				//Inputing data
				tTemp += p2Temp;
				game.addPlayer2Record(p2Temp);
				game.addTotalRecord(tTemp);

				//Change turns
				game.changeTurn();
			}
		}
		//If someone wins
		system("CLS");
		game.printText();
		game.printRecord();
		game.printWinningInfo();

		game.deleteMemory();
		return game.playAgain();
	}
}
