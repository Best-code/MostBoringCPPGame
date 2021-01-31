#include <iostream>
#include <math.h>
#include <vector>
#include <string>

int scoreToWin = 100;
int useCustom;
bool hbn;
int rounds = 0;

class Dice {
public:
	int sides;
	int value;
	bool bIsCustom = false;
	std::vector<int> custom;

	Dice(int sides){
		this->sides=sides;
		value = rand() % sides;
	}

	Dice() {
		sides = 6;
	}

	Dice(std::vector<int> custom) {
		this->custom = custom;
		bIsCustom = true;
	}

	int roll()
	{
		if (!bIsCustom) {
			value = rand() % sides;
			value = 5;
			return value+1;
		}
		else {
			int customRollValue = rand() % 6;
			return custom[customRollValue];
		}
	}
	
};

int starter() {
	return rand() % 3;
}


class Player
{
	int points = 0;

public:
	std::string name;
	std::vector<int> pastVector;
	std::vector<int> customDice;
	Dice dice;

	Player(std::string name) {
		this->name = name;
	}

	int getPoints() {
		return points;
	}

	int roll() {
		int value = dice.roll();
		points += value;
		pastVector.push_back(points);
		system("CLS");
		std::cout << "Woah, you rolled a " << value << " " << std::endl;
		std::cout << name << ", you now have " << points << "!" << std::endl;
		std::cout << "History: ";
		for (int x = 0; x <= rounds; x++) {
			std::cout << pastVector[x] << " ";
		}
		std::cout << std::endl;
		return value;
	}

	void customize() {
		system("CLS");
		std::cout << name <<", enter 6 numbers on the screen.\nThey must add up to 21!" << std::endl;
		bool bIs21 = false;
		while (!bIs21) {
			std::cout << "Reminder: They must add up to 21!" << std::endl;
			int d1, d2, d3, d4, d5, d6 = 0;
			std::cin >> d1 >> d2 >> d3 >> d4 >> d5 >> d6;
			customDice.clear();
			customDice.push_back(d1);
			customDice.push_back(d2);
			customDice.push_back(d3);
			customDice.push_back(d4);
			customDice.push_back(d5);
			customDice.push_back(d6);
			if (d1 + d2 + d3 + d4 + d5 + d6 == 21) {
				bIs21 = true;
			}
		}
		
	}

	void turn() {
		if (useCustom == 1) {
			customize();
			dice.bIsCustom = true;
			dice.custom = customDice;
		}
		std::cout << "\n" << name << " it's your turn to roll!\nPress any key to do so!" << std::endl;
		std::cin.get();
		if(rounds == 0){
			std::cin.get();
		}
		roll();
		trips();
		dice.bIsCustom = false;
	}

	void trips() {
		int x = rounds;
		if (x >= 2) {
			int trueVal = pastVector[x] - pastVector[x - 1];
			if (pastVector[x-1] - trueVal == pastVector[x - 2]) {
				std::cout << "\nTRIPS!!!!\n" << name << ", you lose 10 points!!" << std::endl;
				points -= 10;
			}
		}
		
	}
};


bool winner(Player p1, Player p2) {
	if (p1.getPoints() >= scoreToWin || p2.getPoints() >= scoreToWin)
		return true;
	return false;
}

void gameLoop(Player p1, Player p2) {
	std::cin.get();
	std::cout << "Player one, to find out who goes first, please type 1(heads) or 2(tails)!" << std::endl;
	int pOneInp;
	std::cin >> pOneInp;
	int whoStarts = starter();
	std::cout << ((whoStarts == 1) ? "\nIt's 1(Heads)!" : "\nIt's 2(Tails)!") << std::endl;
	if (whoStarts == pOneInp) {
		std::cout << "Awesome " << p1.name << " you will go first!" << std::endl;
	}
	else {
		std::cout << p2.name << " you will go first!" << std::endl;
	}
	bool l = !winner(p1, p2);
	while (l)
	{
		useCustom = false;

		if (rounds % 10 == 0) {
			if (rounds > 0) {
				std::cout << "\n\n\nYou have made it to round " << rounds << " how... exciting!" << std::endl;
				std::cout << "Would you two like to use a custom dice this round?\n1(yes) or 0(no)" << std::endl;
				std::cin >> useCustom;
				std::cout << ((useCustom == 1) ? "How exciting!" : "Alrighty, maybe next time...") << std::endl;
			}
		}
		if (whoStarts == pOneInp) {
			p1.turn();
			l = !winner(p1, p2);
			p2.turn();
			l = !winner(p1, p2);
			useCustom = 0;
		}
		else {
			p2.turn();
			l = !winner(p1, p2);
			p1.turn();
			l = !winner(p1, p2);
			useCustom = 0;
			
		}
		rounds += 1;

	}

	std::cout << ((p1.getPoints() > p2.getPoints()) ? p1.name : p2.name) << ", Congratulations on winning!" << std::endl;

}

int main()
{

	Player p1("Colin");
	Player p2("Fin");
	bool playAgain = true;

	std::cout << R"(Welcome to the worlds most boring game.
Your Objective is to beat your friend in a race to 100;
You will roll a six sided dice. 
Rolling the same number three times in a row will set you back points.

Ready Let's Begin!
	
Press any key to advance!


)";
	while (playAgain) {
		gameLoop(p1, p2);
		std::cout << std::endl << "Would you like to play again 1(yes) or 0(no)?" << std::endl;
		std::cin >> playAgain;
	}
}