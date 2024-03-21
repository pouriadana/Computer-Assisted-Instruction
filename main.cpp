#include <random>
#include <iostream>

int promptQuestion(int difficulty, int operation);
void response(bool outcome);
int chooseDifficulty();
int chooseOp();

int main()
{
	int userAnswer{ 1 };
	int answersCount{ 0 };
	int correctAnswersCount{ 0 };

	int difficulty{ chooseDifficulty() };
	int operation{ chooseOp() };

	while (userAnswer != -1)
	{
		int correctAnswer{ promptQuestion(difficulty, operation) };
		std::cout << "Enter your answer: ";
		std::cin >> userAnswer;
		answersCount++;

		while ((userAnswer != correctAnswer) && (userAnswer != -1))
		{
			response(false);
			std::cin >> userAnswer;
			answersCount++;
			if (answersCount == 10)
			{
				break;
			}
		}

		if (userAnswer == correctAnswer)
		{
			response(true);
			correctAnswersCount++;
		}

		if (answersCount == 10)
		{
			double percentage{ correctAnswersCount / 10.0 };
			if (percentage < 0.75)
			{
				std::cout << "Please ask your teacher for help.\n";
			}
			else if (percentage >= 0.75)
			{
				std::cout << "Congrats. You're ready to go to the next level!\n";
			}
			std::cout << "Program is reset.\n";
			answersCount = 0;
			correctAnswersCount = 0;

			difficulty = chooseDifficulty();
			operation = chooseOp();
		}
	}
}

int promptQuestion(int difficulty, int operation)
{
	static std::random_device rd;
	static std::default_random_engine engine{ rd() };

	int val_1;
	int val_2;
	switch (difficulty)
	{
		case 1:
		{
			static std::uniform_int_distribution<int> selectOneDigit{ 0, 9 };
			val_1 = selectOneDigit(engine);
			val_2 = selectOneDigit(engine);
			break;
		}
		case 2:
		{
			static std::uniform_int_distribution<int> selectTwoDigit{ 10, 99 };
			val_1 = selectTwoDigit(engine);
			val_2 = selectTwoDigit(engine);
			break;
		}
		case 3:
		{
			static std::uniform_int_distribution<int> selectThreeDigit{ 100, 999 };
			val_1 = selectThreeDigit(engine);
			val_2 = selectThreeDigit(engine);
			break;
		}
	}

	if (operation == 5)
	{
		operation = 1 + rand() % 4;
	}

	int answer{ 0 };
	switch (operation)
	{
	case 1:
		std::cout << "What is " << val_1 << " added to " << val_2 << "?\n";
		answer = val_1 + val_2;
		break;
	case 2:
		std::cout << "What is " << val_1 << " - " << val_2 << "?\n";
		answer = val_1 - val_2;
		break;
	case 3:
		std::cout << "How much is " << val_1 << " times " << val_2 << "?\n";
		answer = val_1 * val_2;
		break;
	case 4:
		std::cout << "What is " << val_1 << " / " << val_2 << "? (truncated)\n";
		answer = val_1 / val_2;
		break;
	}
	return answer;
}

void response(bool outcome)
{
	srand(time(nullptr));

	if (false == outcome)
	{
		switch (const int select{ rand() % 4 })
		{
		case 0:
			std::cout << "No, please try again: ";
			break;
		case 1:
			std::cout << "Wrong. Try once more: ";
			break;
		case 2:
			std::cout << "Don't give up: ";
			break;
		case 3:
			std::cout << "No. Keep trying: ";
			break;
		}
	}
	else
	{
		switch (const int select{ rand() % 4 })
		{
		case 0:
			std::cout << "Very good!\n";
			break;
		case 1:
			std::cout << "Excellent!\n";
			break;
		case 2:
			std::cout << "Nice work!\n";
			break;
		case 3:
			std::cout << "Keep up the good work!\n";
		}
	}
}

int chooseDifficulty()
{
	std::cout << "Choose a difficulty level:\n";
	std::cout << "1 - Easy (single digit)\n2 - Medium (two-digit)\n3 - Hard (triple digit)\n";
	std::cout << "--> ";
	int difficulty;
	std::cin >> difficulty;

	return difficulty;
}

int chooseOp()
{
	std::cout << "Select an operation mode for questions:\n";
	std::cout << "1 - Addition\n2 - Subtraction\n3 - Multiplication\n4 - Division\n5 - Random\n--> ";
	int opMode;
	std::cin >> opMode;

	return opMode;
}
