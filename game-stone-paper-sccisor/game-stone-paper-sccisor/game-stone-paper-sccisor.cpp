#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum gameOption { stone = 1, paper = 2, scissor = 3 };
enum resultGame { win, lose, draw };


string ChoiceName(int choice) {
    switch (choice) {
    case stone: return "Stone";
    case paper: return "Paper";
    case scissor: return "Scissor";
    default: return "Unknown";
    }
}

int RandomNumber(int from, int to) {
    return rand() % (to - from + 1) + from;
}


int HowManyRound() {
    int rounds;
    cout << "Enter number of rounds: ";
    cin >> rounds;

    while (rounds <= 0) {
        cout << "Enter positive number: ";
        cin >> rounds;
    }

    return rounds;
}

int GetUserChoice() {
    int choice;
    cout << "\n1-Stone  2-Paper  3-Scissor\nYour choice: ";
    cin >> choice;
    return choice;
}

bool IsValidChoice(int choice) {
    return choice >= 1 && choice <= 3;
}


resultGame DetermineWinner(int user, int computer) {

    if (user == computer) {
        system("color E0");   
        return draw;
    }

    if ((user == stone && computer == scissor) ||
        (user == paper && computer == stone) ||
        (user == scissor && computer == paper)) {

        system("color A0");   
        return win;
    }

    system("color C0");      
    return lose;
}



resultGame StartRound(int& userChoice, int& computerChoice) {

    userChoice = GetUserChoice();

    while (!IsValidChoice(userChoice)) {
        cout << "Invalid choice!\n";
        userChoice = GetUserChoice();
    }

    computerChoice = RandomNumber(1, 3);

    cout << "\nYou chose: " << ChoiceName(userChoice) << endl;
    cout << "Computer chose: " << ChoiceName(computerChoice) << endl;

    return DetermineWinner(userChoice, computerChoice);
}


void DisplayResult(resultGame result) {

    if (result == win)
        cout << ">>> YOU WIN THIS ROUND\n";
    else if (result == lose)
        cout << ">>> YOU LOSE THIS ROUND\n";
    else
        cout << ">>> DRAW\n";
}

void ShowStatistics(int round, int win, int lose, int draw) {

    cout << "\n--- STATISTICS ---\n";
    cout << "Rounds: " << round << endl;
    cout << "Win: " << win << endl;
    cout << "Lose: " << lose << endl;
    cout << "Draw: " << draw << endl;
}


void PlayGame() {

    char again;

    do {

        system("cls");
        system("color 07");

        int rounds = HowManyRound();

        int winCount = 0, loseCount = 0, drawCount = 0;

        for (int i = 1; i <= rounds; i++) {

            cout << "\n========== ROUND " << i << " ==========\n";

            int user, computer;
            resultGame result = StartRound(user, computer);

            DisplayResult(result);

            if (result == win) winCount++;
            else if (result == lose) loseCount++;
            else drawCount++;
        }

        ShowStatistics(rounds, winCount, loseCount, drawCount);

        cout << "\nPlay again? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');
}


int main() {

    srand((unsigned)time(NULL));
    PlayGame();
}
