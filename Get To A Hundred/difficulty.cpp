#include <iostream>
#include <stdlib.h>
#include "Difficulty.h"
using namespace std;

Difficulty::Difficulty(int i) {
	type = modes[i];

	if (i == 1) {
		medType = (rand() % 6) + 1;
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

int Difficulty::getNumber(int tTemp, int winningNum) {
	if (getType().compare(modes[0]) == 0) return getNumberEasy(tTemp, winningNum);
	else if (getType().compare(modes[1]) == 0) return getNumberMedium(tTemp, winningNum);
	else return getNumberHard(tTemp, winningNum);
}

int Difficulty::getNumberEasy(int tTemp, int winningNum) {
	if (winningNum == 100) return winningNum - tTemp;
	return (rand() % 10) + 1;
}

int Difficulty::getNumberMedium(int tTemp, int winningNum) {
	int n = (rand() % 2);
	switch (medType) {
	case 1:
		if (winningNum > 67) return getNumberHard(tTemp, winningNum);
		else return (rand() % 10) + 1;
	case 2:
		setMedType(3);
		return getNumberHard(tTemp, winningNum); //(i.e "Hard") not Rand -> Rand -> Repeat
	case 3:
		setMedType(2);
		return getNumberEasy(tTemp, winningNum); //(i.e "Easy") Rand -> not Rand -> Repeat
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
	default:
		break;
	}
}

int Difficulty::getNumberHard(int tTemp, int winningNum) {
	if (tTemp != winningNum) return winningNum - tTemp;
	return (rand() % 10) + 1;
}