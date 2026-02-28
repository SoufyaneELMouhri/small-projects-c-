#include <iostream>
#include <time.h>
#include <string>
#include <windows.h>
using namespace std;

enum enLevelQuizz { eHard = 1, eMed = 2, eEasy = 3, eMixLevel = 4 };
enum enFinalResult { eFail = 1, ePass = 2 };
enum enTypeOperationQuizz { eAdd = 1, eSub = 2, eMul = 3, eDiv = 4, eMix = 5 };

struct stQuizzInfo {
    int ansowerCorrect;
    int ansowerUser;
    bool isCorrect;
    int num1;
    int num2;
    enTypeOperationQuizz operation;
};

struct stResaultFinal {
    enLevelQuizz level;
    enTypeOperationQuizz operation;
    enFinalResult finalResult;
    int totalQhuizz;
    int totalCorrectAnsower;
    int totalWrongAnsower;
};

int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

int GetRangeByLevel(enLevelQuizz level) {
    switch (level) {
    case eEasy:     return 10;
    case eMed:      return 50;
    case eHard:     return 100;
    case eMixLevel: return RandomNumber(10, 100);
    default:        return 10;
    }
}

enTypeOperationQuizz ResolveOperation(enTypeOperationQuizz op) {
    if (op == eMix) return (enTypeOperationQuizz)RandomNumber(1, 4);
    return op;
}

string GetOperationSymbol(enTypeOperationQuizz op) {
    switch (op) {
    case eAdd: return "+";
    case eSub: return "-";
    case eMul: return "*";
    case eDiv: return "/";
    default:   return "?";
    }
}

int CalcCorrectAnswer(int num1, int num2, enTypeOperationQuizz op) {
    switch (op) {
    case eAdd: return num1 + num2;
    case eSub: return num1 - num2;
    case eMul: return num1 * num2;
    case eDiv: return num1 / num2;
    default:   return 0;
    }
}

stQuizzInfo GenerateQuestion(int qNum, enLevelQuizz level, enTypeOperationQuizz op) {
    stQuizzInfo q;
    int maxVal = GetRangeByLevel(level);
    q.operation = ResolveOperation(op);

    if (q.operation == eDiv) {
        q.num2 = RandomNumber(1, maxVal);
        q.num1 = q.num2 * RandomNumber(1, 10);
    }
    else {
        q.num1 = RandomNumber(1, maxVal);
        q.num2 = RandomNumber(1, maxVal);
    }

    q.ansowerCorrect = CalcCorrectAnswer(q.num1, q.num2, q.operation);

    cout << "\nQuestion [" << qNum << "] : ";
    cout << q.num1 << " " << GetOperationSymbol(q.operation) << " " << q.num2 << " = ";
    cin >> q.ansowerUser;

    q.isCorrect = (q.ansowerUser == q.ansowerCorrect);
    return q;
}

void ShowQuestionResult(const stQuizzInfo& q) {
    if (q.isCorrect) {
        system("color 2F");
    }
    else {
        system("color 4F");
    }
    cout << "\n========================================\n";
    if (q.isCorrect) {
        cout << "  Correct! Well done!\n";
    }
    else {
        cout << "  Wrong! Correct answer is: " << q.ansowerCorrect << "\n";
    }
    cout << "========================================\n";
}

enLevelQuizz AskLevel() {
    int choice;
    cout << "\nSelect Level:\n";
    cout << "  [1] Hard\n  [2] Medium\n  [3] Easy\n  [4] Mix\n";
    cout << "Your choice: ";
    cin >> choice;
    if (choice < 1 || choice > 4) choice = 3;
    return (enLevelQuizz)choice;
}

enTypeOperationQuizz AskOperation() {
    int choice;
    cout << "\nSelect Operation:\n";
    cout << "  [1] Addition (+)\n  [2] Subtraction (-)\n  [3] Multiplication (*)\n  [4] Division (/)\n  [5] Mix\n";
    cout << "Your choice: ";
    cin >> choice;
    if (choice < 1 || choice > 5) choice = 1;
    return (enTypeOperationQuizz)choice;
}

int AskNumberOfQuestions() {
    int n;
    cout << "\nHow many questions? ";
    cin >> n;
    if (n < 1) n = 3;
    return n;
}

void ShowFinalResult(const stResaultFinal& result) {
    if (result.finalResult == ePass) {
        system("color 2F");
    }
    else {
        system("color 4F");
    }
    cout << "\n========================================\n";
    cout << "           FINAL RESULT\n";
    cout << "========================================\n";
    cout << "Total Questions : " << result.totalQhuizz << "\n";
    cout << "Correct         : " << result.totalCorrectAnsower << "\n";
    cout << "Wrong           : " << result.totalWrongAnsower << "\n";
    if (result.finalResult == ePass) {
        cout << "\n  YOU PASSED! Well done!\n";
    }
    else {
        cout << "\n  YOU FAILED! Try again.\n";
    }
    cout << "========================================\n";
}

void StartQuizz() {
    srand((unsigned)time(NULL));

    enLevelQuizz         level = AskLevel();
    enTypeOperationQuizz op = AskOperation();
    int                  total = AskNumberOfQuestions();

    stResaultFinal result;
    result.level = level;
    result.operation = op;
    result.totalQhuizz = total;
    result.totalCorrectAnsower = 0;
    result.totalWrongAnsower = 0;

    cout << "\n========== Quiz Start ==========\n";

    for (int i = 1; i <= total; i++) {
        stQuizzInfo q = GenerateQuestion(i, level, op);
        ShowQuestionResult(q);
        if (q.isCorrect) result.totalCorrectAnsower++;
        else             result.totalWrongAnsower++;
    }

    result.finalResult = (result.totalCorrectAnsower > result.totalWrongAnsower) ? ePass : eFail;
    ShowFinalResult(result);
}

void PlayQuizz() {
    char again;
    do {
        system("color 07");
        StartQuizz();
        cout << "\nPlay again? (y/n): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');

    system("color 07");
    cout << "\nGoodbye!\n";
}

int main() {
    PlayQuizz();
    return 0;
}
