#include "List.h"
#include "Difficulty.h"
#pragma once

class GetToAHundred {
private:
	int mode;
	int randnum;

	int winningNums[11] = { 1, 12, 23, 34, 45, 56, 67, 78, 89, 100 };
	int* wNPtr;
	List* total;
	List* player1;
	List* player2; //or computer
	Difficulty* diff;

	int turn;
	int win;

public:
	GetToAHundred(int mode);

	GetToAHundred(int mode, int lvl);

	int inputCheck(string in);

	int winCheck();

	int getPlayerNumber();

	void addPlayer1Record(int p1Temp);

	void addPlayer2Record(int p2Temp);

	void addTotalRecord(int tTemp);

	void changeTurn();

	int getTurn();

	int getComputerNumber(int tTemp, int pTemp);

	int getWinningNum(int tTemp);

	void printText();

	void printRecord();

	void printWinningInfo();

	int playAgain();

	void deleteMemory();
};