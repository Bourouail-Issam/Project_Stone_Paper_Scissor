#include <iostream>
using namespace std;

enum enChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enStatuRouns { UserWin = 10, ComputerWin = 20, NoWinner = 30 };

void ResetScreen() {
	system("cls");
	system("color 0F");
}
int ReadeNumberWithInterval(int From, int To, string Msg) {
	int number = 0;
	do{
		cout << Msg;
		cin >> number;

	} while (number > To  || number < From ); 
	return number;
}
int Random(int From, int To) {
	int Random = rand() % (To - From + 1) + From;
	return Random;
}

enStatuRouns RoudResult(int UserChoice, int ComputerChoice) {

	//if (enChoice::Stone == UserChoice) {
	//	if (ComputerChoice == enChoice::Stone) {
	//		return enStatuRouns::NoWinner;
	//	}
	//	else if (ComputerChoice == enChoice::Paper) {
	//		return enStatuRouns::ComputerWin;
	//	}
	//	else {
	//		return enStatuRouns::UserWin;
	//	}
	//}
	//else if (enChoice::Paper == UserChoice) {
	//	if (ComputerChoice == enChoice::Stone) {
	//		return enStatuRouns::UserWin;
	//	}
	//	else if (ComputerChoice == enChoice::Paper) {
	//		return enStatuRouns::NoWinner;
	//	}
	//	else {
	//		return enStatuRouns::ComputerWin;
	//	}
	//}
	//else {
	//	if (ComputerChoice == enChoice::Stone) {
	//		return enStatuRouns::ComputerWin;
	//	}
	//	else if (ComputerChoice == enChoice::Paper) {
	//		return enStatuRouns::UserWin;
	//	}
	//	else {
	//		return enStatuRouns::NoWinner;
	//	}
	//}
	
	// Improve Program performance

	if (UserChoice == ComputerChoice)
		return enStatuRouns::NoWinner;
	switch (UserChoice)
	{
	case enChoice::Paper:
		if(ComputerChoice == enChoice::Scissors)
			return enStatuRouns::ComputerWin;

	case enChoice::Scissors:
		if (ComputerChoice == enChoice::Stone)
			return enStatuRouns::ComputerWin;

	case enChoice::Stone:
		if (ComputerChoice == enChoice::Paper)
			return enStatuRouns::ComputerWin;
	}
	return enStatuRouns::UserWin;
}

string choiceToString(int YourChoice) {
	if (YourChoice == enChoice::Stone)
		return "Stone";
	else if (YourChoice == enChoice::Paper)
		return "paper";
	else 
		return "Scissors";
}
string RoundStatus(enStatuRouns StatusRound) {
	if (StatusRound == enStatuRouns::UserWin)
		return "user";
	else if (StatusRound == enStatuRouns::ComputerWin)
		return "Computer";
	else
		return "No Winner";
}
void PrintRound(enStatuRouns StatusRound, int NumberRounds, int UserChoice, int ComputerChoice) 
{
	string WinnerRound = "", choiceUser = "", choiceComputer = "";

	cout << "\n\n____________Round["<< NumberRounds <<"]____________\n\n";
	cout << "Player1  Choice : " << choiceToString(UserChoice) << endl;
	cout << "Copmuter Choice : " << choiceToString(ComputerChoice);
	cout << "\nRound Winner    : " << RoundStatus(StatusRound);
	cout << "\n\n___________________________________\n\n";
}

void ResultGame(int RoudsGame, int PlayerNumberWin, int ComputerNumberWin, int NoWinner)
{
	string  WinnerGame = "";

	if (PlayerNumberWin > ComputerNumberWin)
	{
		WinnerGame = "Player1";
		system("color 2F"); //turn screen to Green
	}
	else if (PlayerNumberWin < ComputerNumberWin)
	{
		WinnerGame = "Computer";
		system("color 4F"); //turn screen to Red  
	}
	else
	{
		WinnerGame = "No Winner";
		system("color 6F"); //turn screen to Yellow
	}


	cout << "\n\n                   ___________________________________________________\n\n";
	cout << "                                +++ G a m e  O v e r +++";
	cout << "\n\n                   ___________________________________________________\n\n";
	cout << "                   __________________ [ Game Result ] ________________\n\n";
	cout << "                     Game Rounds         : " << RoudsGame << endl;
	cout << "                     Player1 won times   : " << PlayerNumberWin;
	cout << "\n                     Computer won times  : " << ComputerNumberWin;
	cout << "\n                     Draw times          : " << NoWinner;
	cout << "\n                     Final Winner        : " << WinnerGame;
}
void AllGame()
{
	int UserChoice[10], ComputerChoice[10], NumberRounds;;
	char FinishGame;
	enStatuRouns StatusRound;

	do{
		ResetScreen();
		int  NumberUserWin = 0, NumberComputer = 0, NoWinner = 0;

		NumberRounds = ReadeNumberWithInterval(1, 10, "How Many Rounds 1 to 10 ?\n: ");

		for (int i = 0; i < NumberRounds; i++) {

			UserChoice[i] = ReadeNumberWithInterval(1, 3, "\n\nYour choice: [1]:Stone, [2]:Paper, [3]:Scissors ? \n : ");
			ComputerChoice[i] = Random(1, 3);
			StatusRound = RoudResult(UserChoice[i], ComputerChoice[i]);

			switch (StatusRound){

			case enStatuRouns::UserWin:
				NumberUserWin++;
				system("color 2F"); //turn screen to Green
				break;

			case enStatuRouns::ComputerWin:
				NumberComputer++;
				system("color 4F"); //turn screen to Red  
				break;

			case enStatuRouns::NoWinner:
				NoWinner++;
				system("color 6F"); //turn screen to Yellow
				break;
			}

			PrintRound(StatusRound, i + 1, UserChoice[i],ComputerChoice[i]);
		}

		ResultGame(NumberRounds, NumberUserWin, NumberComputer, NoWinner);

		cout << "\n\nDo you want to paly again ? Y/N \n: ";
		cin >> FinishGame;

	} while (FinishGame == 'Y' || FinishGame == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	AllGame();
	system("pause>");
	return 0;
}

