// Project - 2 - Math - Game

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };


int ReadRandomNumber(int From, int To)

{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;


}
enQuestionLevel ReadQuestionLevel()
{


	short QuestionLeve = 0;
	do
	{
		cout << "\n Enter question level [1]:EasyLevel,[2]:MedLevel,[3]:HardLevel,[4]:Mix ?\n";
		cin >> QuestionLeve;





	} while (QuestionLeve < 1 || QuestionLeve > 4);

	return enQuestionLevel(QuestionLeve);

}
enOperationType ReadOpType()
{


	short OpType;
	do
	{
		cout << "\n Enter Operation Type[1]:Add, [2] : Sub, [3] : Mul, [4] : Div , [5]:Mix ? \n";
		cin >> OpType;





	} while (OpType < 1 || OpType > 5);

	return  enOperationType(OpType);

}
short ReadHowManyQuestions()
{

	short NumberOfQuestions;
	do
	{
		cout << "\n How many question do you want to answer ?\n";
		cin >> NumberOfQuestions;





	} while (NumberOfQuestions < 1 || NumberOfQuestions >10);

	return  NumberOfQuestions;
}


string GetTypeSymbol(enOperationType OpType)
{

	switch (OpType)
	{
	case enOperationType::Add:
		return "+";


	case  enOperationType::Sub:
		return "-";


	case enOperationType::Mul:
		return "X";


	case enOperationType::Div:
		return "/";


	default:
		return  "Mix";

	}





}
string GetQuestionLevleText(enQuestionLevel QuestionLevel)
{

	string arrQuestionLevle[4] = { "EasyLevel","MedLevel" , "HardLevel" , "Mix" };

	return arrQuestionLevle[QuestionLevel - 1];


}

struct stQuestion
{

	short Number1 = 0;
	short Number2 = 0;
	enQuestionLevel QuestionLevel;
	enOperationType  OperationType;
	short CorrectAnswer = 0;
	short PlayerAnswer = 0;
	bool AnswerResult = false;

};
struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionLevel QuestionsLevel;
	enOperationType  OpType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool IsPass = false;

};

int SimpleCalculator(int Number1, int Number2, enOperationType  OpType)
{
	switch (OpType)
	{

	case  enOperationType::Add:
		return Number1 + Number2;
	case  enOperationType::Sub:
		return Number1 - Number2;
	case  enOperationType::Mul:
		return Number1 * Number2;
	case  enOperationType::Div:
		return Number1 / Number2;

	default:
		return Number1 + Number2;

	}







}


stQuestion  GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType  OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)ReadRandomNumber(1, 3);
	}
	if (OpType == enOperationType::MixOp)
	{
		OpType = (enOperationType)ReadRandomNumber(1, 4);
	}
	Question.OperationType = OpType;

	switch (QuestionLevel)
	{

	case enQuestionLevel::EasyLevel:
		Question.Number1 = ReadRandomNumber(1, 10);
		Question.Number2 = ReadRandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::MedLevel:
		Question.Number1 = ReadRandomNumber(10, 50);
		Question.Number2 = ReadRandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::HardLevel:
		Question.Number1 = ReadRandomNumber(50, 100);
		Question.Number2 = ReadRandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;


	}
	return Question;


}
void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (int Question = 0; Question <= Quizz.NumberOfQuestions; Question++)
	{


		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);




	}

}

void PrintTheQuestion(stQuizz& Quizz, int QuestionNumber)
{

	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]" << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2;
	cout << GetTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n_____________________________\n";






}
int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return  Answer;



}
void SetAnswerScreenColor(bool AnswerResult)
{
	switch (AnswerResult)
	{
	case 1:
		system("color 2F");
		break;

	case 0:
		system("color 4F");
		cout << "\a";
		break;


	}
}

void CorrectTheQewstionAnswer(stQuizz& Quizz, int QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong answer -:(\n";
		cout << "The correct answer is :";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{

		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Wright answer -:)\n";

		cout << endl;


	}
	SetAnswerScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);


}
void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
	for (int QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQewstionAnswer(Quizz, QuestionNumber);


	}

	Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);



}
string GetFinalResultText(bool Pass)
{
	if (Pass)
		return "Pass:-)";
	else
		return "Fail:-(";




}
void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n______________________________________\n\n";
	cout << "Final Result is:" << GetFinalResultText(Quizz.IsPass);
	cout << "\n_______________________________________\n\n";

	cout << "Number Of Questions    :" << Quizz.NumberOfQuestions << endl;
	cout << "Question Level         :" << GetQuestionLevleText(Quizz.QuestionsLevel) << endl;
	cout << "Operation Type         :" << GetTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Right Answer :" << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answer :" << Quizz.NumberOfWrongAnswers << endl;
	cout << "___________________________________________________\n\n";

}





void  PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);
	PrintQuizzResults(Quizz);

}

void ResetScreen()
{
	system("cls");
	system("color 0F");

}

void StartQuizz()
{


	char   PlayAgain = 'Y';

	do {

		ResetScreen();
		PlayMathGame();



		cout << endl << "Do you want to Play again ? Y/N? \n ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}


int main()
{


	srand((unsigned)time(NULL));


	StartQuizz();



	return 0;
}
