# Get-To-A-Hundred
[README.txt](https://github.com/michaelrw19/Get-To-A-Hundred/files/7841753/README.txt)

*If the format or spacing below is bad and make the document unclear, take a look at README.txt*

Note: A multiplayer version (PvP) will be added soon

This program is a math game called "Get to a Hundred". 
The game can be played by 2 player, in this version a human player will be playing with a computer.

How to play the game:
1. Read the instructions / rules printed by the program.
2. Pick the level of difficulty.
3. If it's your turn to enter a number, enter a number between 1-10.
4. If it's the computer's turn, wait.
5. Keep playing until one of the players reach 100.

============================================================================================================

This program accept several inputs that will determine the difficulty, accepts the player's number, 
and determine whether the player wants to play again or quit the game. The program will also roll a
random number that will determine who among the 2 players will enter a number first.

Everytime the player and the computer enter a number it will be stored and printed to show the record.
Another purpose of this is to let the player think what number would be needed to reach a certain number.

Also, the program will purposely delay a few seconds during the computer's turn, so this doens't mean that 
the program is not responding.

The program also handles wrong input. For instance, a player entered a number other than 1-10, or 
the player enters a non digit character. A loop will occur until the player enter the right input or
until the player wants to quit the game by entering 'q'.

============================================================================================================
WARNING: Read this if you want to understand how the program works. Reading this would also reveal how to win the game easily.
	 If you want to challenge yourself and beat the algorithm skip this part, and figure out how to win the game by yourself.

Computer's algorithm to determine the number to be entered:

Inside the cVp.cpp, a list of number is defined. These numbers are the needed numbers to be reached in order 
to win the game, we call this winningNum. Everytime the computer get its turn, it will figure out the next possible 
winningNum by using getWinningNum(). 

The number that the computer will enter is calculated in file Difficulty.cpp and also determined by the level of difficulty
that the player decided at the beginning of the game.

Difficulty: Easy | Function: getNumberEasy(int tTemp, int winningNum)
-> The computer will keep entering a random number from 1-10 until the winningNum is 100

Difficulty: Hard | Function: getNumberHard(int tTemp, int winningNum)
-> The computer will calculate and enter the number needed to reach the winningNum. 
-> If previously the player has enter a number that reacher the winning number, then it will enter a random number between 10. 
Why? Because in order to go from one winningNum to another winningNum, it takes a number greater than 10
(maximum number any player can enter is 10)

Difficulty: Medium | Function: getNumberMedium(int tTemp, int winningNum)
-> In this difficulty there are 7 different algorithms that will produce the number for the computer in different ways.
   These 6 algorithm are implemented based on a random number from 1-6. Each number represent the algorithm that will be used.

-> Algorithm 1
	- The computer will keep entering a random number from 1-10 until the winningNum is greater than or equal to 67
-> Algorithm 2
	- The computer will use getNumberHard(), the next turn it'll use getNumberEasy(), and back to getNumberHard()
-> Algorithm 3
	- Same as Algorithm 2, but it starts with getNumberEasy(), then getNumberHard(), and so on
-> Algorithm 4
	Note: In algorithm 4 and 5, variable chances (initialized a random number from 1-5) and variable n 
	(initialized by a random number, 0 or 1) will be used.
	- The computer will use getNumberEasy for chances times if and only if n is equal to 1. If chances = 0 or n = 0, then
	the computer will use getNumberHard
-> Algorithm 5
 	- The computer will use getNumberHard for chances times if and only if n is equal to 1. If chances = 0 or n = 0, then
	the computer will use getNumberEasy
-> Algorithm 6
	- The computer will either use getNumberHard() or getNumberEasy() based on the value of n. If n = 1, use getNumberHard(),
	else use getNumberEasy()
-> Algorithm 7
	- The computer will mimic the player's number until the winningNum is greater than or equal to 89, 
	- If the player hasn't enter a number (The computer enter the number first), return a random number

Note:
1. Variable chances are intialized in constructor Difficulty(int i)
2. Variable n is initialized everytime getNumberMedium() is called.

============================================================================================================
