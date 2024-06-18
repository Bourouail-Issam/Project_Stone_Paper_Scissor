
#include <iostream>
using namespace std;
enum enChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Palayer = 1, Computer = 2, Draw = 3 };

//Game-Stone-Paper-Scissor

struct stRoundInfo {
	short NumberRounds;
	enChoice ChoicePalayer1;
	enChoice ChoiceComputer;
	enWinner RoundWinner;
	string NameRoundWinner;
};
struct stGameResults{
	short GameRounds = 0;
	short NumberWinTimesOfPlayer1 = 0;
	short NumberWinTimesOfComputer = 0;
	short NumebrDraw = 0;
	enWinner WinnerGame;
	string WinnerName;
};
void ResetScreen() {
	system("cls");    
	system("color 0F");
}
int Random(int From, int To) {
	int Random = rand() % (To - From + 1) + From;
	return Random;
}
string Tabs(int number) {
	string NumberTab = "";
	for (short i = 0; i < number; i++)
		NumberTab += "\t";
	return NumberTab;
}
void ShowGameOverScreen() {
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
	cout << Tabs(2) << "__________________________________________________________\n\n";
}
int ReadHowManyRounds() {
	int number = 0;
	do {
		cout << "How Many Rounds 1 to 10 ?\n: ";
		cin >> number;

	} while (number < 1 || number > 10);
	return number;
}

enChoice ReadChoicePlayer() {
	int number = 0;
	do {
		cout << "Your choice: [1]:Stone, [2]:Paper, [3]:Scissors ? \n : ";
		cin >> number;

	} while (number < 1 || number > 3);
	return (enChoice)number;
}
enChoice ChoiceComputer() {
	int choiceComputer = Random(1, 3);
	return (enChoice)choiceComputer;
}

string WinnerName(enWinner RoundWinner) {
	string arrWinnerGame[3] = { "[Player1]", "[Computer]", "[Draw]" };
	return arrWinnerGame[(int)RoundWinner - 1];
}
string ChoiceName (enChoice choice) {
	string arrGameChoice [3] = { "Stone", "Paper", "Scissors" };
	return arrGameChoice[(int)choice - 1];
}


enWinner whoWinnerInRound(stRoundInfo RoundInfo) {

	if (RoundInfo.ChoicePalayer1 == RoundInfo.ChoiceComputer)
		return enWinner::Draw;
	switch (RoundInfo.ChoicePalayer1) {
	case enChoice::Paper:
		if (RoundInfo.ChoiceComputer == enChoice::Scissors)
			return enWinner::Computer;
	case enChoice::Stone:
		if (RoundInfo.ChoiceComputer == enChoice::Paper)
			return enWinner::Computer;
	case enChoice::Scissors:
		if (RoundInfo.ChoiceComputer == enChoice::Stone)
			return enWinner::Computer;
		//if you reach here then player1 is the winner.
		return enWinner::Palayer;
	}
}
enWinner WhoWonTheGame(int PlyerWin, int ComputerWin, int NumberDraw) {
	if (PlyerWin > ComputerWin)
		return enWinner::Palayer;
	if (PlyerWin < ComputerWin)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

void SetWinnerScreenColor(enWinner Winner) {
	switch (Winner) {
	case enWinner::Palayer :
		system("color 2F"); //turn screen to Green
		break;
	case enWinner::Computer :
		system("color 4F"); //turn screen to Red     
		cout << "\a";
		break;
	default :
		system("color 6F"); //turn screen to Yellow
		break; 
	}
}
void PrintRound(stRoundInfo RoundInfo) {
	cout << "\n\n--------------[" << RoundInfo.NumberRounds << "]--------------\n\n";
	cout << "Player1  Choice : " << ChoiceName(RoundInfo.ChoicePalayer1) << endl;
	cout << "Copmuter Choice : " << ChoiceName(RoundInfo.ChoiceComputer);
	cout << "\nRound Winner    : " << WinnerName(RoundInfo.RoundWinner);
	cout << "\n\n____________________________________________________\n\n\n\n\n\n";
}

stGameResults FillGameResults(int HowManyRounds, int PlyerWin, int ComputerWin, int NumberDraw) {
	
	stGameResults ResultGame;

	ResultGame.GameRounds = HowManyRounds;
	ResultGame.NumberWinTimesOfPlayer1 = PlyerWin;
	ResultGame.NumberWinTimesOfComputer = ComputerWin;
	ResultGame.NumebrDraw = NumberDraw;
	ResultGame.WinnerGame = WhoWonTheGame(PlyerWin, ComputerWin, NumberDraw);
	ResultGame.WinnerName = WinnerName(ResultGame.WinnerGame);
	return ResultGame;
}
stGameResults PlayGame(int HowManyRounds) {

	stRoundInfo RoundInfo;
	int PlyerWin = 0, ComputerWin = 0, NumberDraw = 0;

	for (short round = 0; round < HowManyRounds; round++) {

		RoundInfo.NumberRounds = round+1;
		RoundInfo.ChoicePalayer1 = ReadChoicePlayer();
		RoundInfo.ChoiceComputer = ChoiceComputer();
		RoundInfo.RoundWinner = whoWinnerInRound(RoundInfo);
		RoundInfo.NameRoundWinner = WinnerName(RoundInfo.RoundWinner);

		SetWinnerScreenColor(RoundInfo.RoundWinner);
		if (enWinner::Palayer == RoundInfo.RoundWinner)
			PlyerWin++;
		else if (enWinner::Computer == RoundInfo.RoundWinner)
			ComputerWin++;
		else
			NumberDraw++;
		PrintRound(RoundInfo);
	}
	return FillGameResults(HowManyRounds, PlyerWin, ComputerWin, NumberDraw);
}
void ShowFinalGameResults(stGameResults ResultGame) {
	cout << "                     Game Rounds         : " << ResultGame.GameRounds << endl;
	cout << "                     Player1 won times   : " << ResultGame.NumberWinTimesOfPlayer1;
	cout << "\n                     Computer won times  : " << ResultGame.NumberWinTimesOfComputer;
	cout << "\n                     Draw times          : " << ResultGame.NumebrDraw;
	cout << "\n                     Final Winner        : " << ResultGame.WinnerName;
}

void StartGame() {
	char PlayAgain = 'Y';
	do{
		ResetScreen();
		stGameResults ResultGame= PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		SetWinnerScreenColor(ResultGame.WinnerGame);
		ShowFinalGameResults(ResultGame);
		cout << "\n\nDo you want to paly again ? Y/N \n: ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}
