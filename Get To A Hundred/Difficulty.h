#include <string>
using namespace std;

class Difficulty {
private:
	const string modes[3] = { "Easy", "Moderate", "Hard" }; //Moderate = Medium
	string type;
	int medType;
	int chances;

public:
	Difficulty(int i);

	void setType(string type);

	string getType();

	void setMedType(int i);

	int getMedType(); 

	void setChances(int i);

	int getChances();

	int getNumber(int tTemp, int winningNum);

	int getNumberEasy(int tTemp, int winningNum);

	int getNumberMedium(int tTemp, int winningNum);

	int getNumberHard(int tTemp, int winningNum);
};
