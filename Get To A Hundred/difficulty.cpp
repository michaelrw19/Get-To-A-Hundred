#include <iostream>
#include <stdlib.h>
#include "Difficulty.h"
using namespace std;

Difficulty::Difficulty(int i) {
	/*
	* i = 0, Difficulty = Easy
	* i = 1, Difficulty = Medium
	* i = 2, Difficulty = Hard
	*/
	i--; //Index starts from 0, need to be decrease by 1
	type = modes[i];
	if (i == 1) {
		//Get the type of algorithm randomly
		medType = (rand() % 7) + 1;
		if (medType == 4 || medType == 5) {
			chances = (rand() % 5) + 1;
		}
	}
}

void Difficulty::setType(string type) {
	this->type = type;
}

string Difficulty::getType() {
	return type;
}

void Difficulty::setMedType(int i) {
	this->medType = i;
}

int Difficulty::getMedType() {
	return medType;
}

void Difficulty::setChances(int i) {
	this->chances = i;
}

int Difficulty::getChances() {
	return chances;
}

//Return a number for the computer
int Difficulty::getNumber(int tTemp, int winningNum, int pTemp) {
	if (getType().compare(modes[0]) == 0) return getNumberEasy(tTemp, winningNum);
	else if (getType().compare(modes[1]) == 0) return getNumberMedium(tTemp, winningNum);
	else return getNumberHard(tTemp, winningNum);
}

//Return a random number from 1-10 if the winningNum is not 100
//Return the number to reach 100 otherwise
int Difficulty::getNumberEasy(int tTemp, int winningNum) {
	if (winningNum == 100) return winningNum - tTemp;
	return (rand() % 10) + 1;
}

/*
* medType = 1
*	Return a random number until the winningNum is greater than 67
* medType = 2
*	Return getNumberHard(), then getNumberEasy(), then getNumberHard() again, and so on
* medType = 3
*	Same as medType = 2, but it starts with getNumberEasy(), then getNumberHard(), and so on
* medType = 4
*	Return getNumberEasy() for chances (variable) times randomly (if n = 1). return getNumberHard() otherwise
* medType = 5
* 	Return getNumberHard() for chances (variable) times randomly (if n = 1). return getNumberEasy() otherwise
* medType = 6
*	Return getNumberHard() or getNumberEasy() randomly.
* medType = 7 (in progress)
*	Return a number that the player entered until the winningNum is 100, 
*	If the player hasn't enter a number (randnum = 0, computer enter the number first), return a random number
*/
int Difficulty::getNumberMedium(int tTemp, int winningNum, int pTemp) {
	int n = (rand() % 2);
	switch (medType) {
	case 1:
		if (winningNum > 67) return getNumberHard(tTemp, winningNum);
		else return (rand() % 10) + 1;
	case 2:
		setMedType(3);
		return getNumberHard(tTemp, winningNum);
	case 3:
		setMedType(2);
		return getNumberEasy(tTemp, winningNum);
	case 4:
		if (n && chances != 0) {
			setChances(getChances() - 1);
			return getNumberEasy(tTemp, winningNum);
		}
		return getNumberHard(tTemp, winningNum);
	case 5:
		if (n && chances != 0) {
			setChances(getChances() - 1);
			return getNumberHard(tTemp, winningNum);
		}
		return getNumberEasy(tTemp, winningNum);
	case 6:
		if (n) return getNumberHard(tTemp, winningNum);
		else return getNumberEasy(tTemp, winningNum);
	case 7:
		if (winningNum >= 89) return getNumberHard(tTemp, winningNum);
		if (pTemp == 0) return (rand() % 10) + 1;
		return pTemp;
	default:
		break;
	}
}

//Return a number that will always lead to the winning numbers only if the winning numbers havent been reached
//otherwise return a random number
int Difficulty::getNumberHard(int tTemp, int winningNum) {
	if (tTemp != winningNum) return winningNum - tTemp;
	return (rand() % 10) + 1;
}

//Note: a more in-dept explanation about the functions can be found in the README.txt
