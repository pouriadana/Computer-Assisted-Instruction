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
	if (-1 == difficulty)
	{
		return 1;
	}

	int operation{ chooseOp() };
	if (-1 == operation)
	{
		return 1;
	}

	while (userAnswer != -999)
	{
		int correctAnswer{ promptQuestion(difficulty, operation) };
		std::cout << "Enter your answer (-999 to quit): ";
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

	static std::uniform_int_distribution<int> distributions[] = {
		std::uniform_int_distribution<int>{0, 9},
		std::uniform_int_distribution<int>{10, 99},
		std::uniform_int_distribution<int>{100, 999}
	};

	int val_1;
	int val_2;
	
	val_1 = distributions[difficulty - 1](engine);
	val_2 = distributions[difficulty - 1](engine);

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
			std::cout << "Incorrect. Please try again: ";
			break;
		case 1:
			std::cout << "That's not quite right. Try once more: ";
			break;
		case 2:
			std::cout << "Incorrect, but don't give up. Give it another shot: ";
			break;
		case 3:
			std::cout << "Wrong answer. Keep trying: ";
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
	std::cout << "Choose a difficulty level (-1 to quit):\n";
	std::cout << "1 - Easy (single digit)\n2 - Medium (double digit)\n3 - Hard (triple digit)\n";
	std::cout << "--> ";
	int difficulty{};

	while (!(std::cin >> difficulty) || difficulty < 1 || difficulty > 3)
	{
		// Exit the program
		if (-1 == difficulty)
		{
			return -1;
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid choice. Please enter a number between 1 and 3: ";
		}
	}
	return difficulty;
}

int chooseOp()
{
	std::cout << "Select an operation mode for questions (-1 to quit):\n";
	std::cout << "1 - Addition\n2 - Subtraction\n3 - Multiplication\n4 - Division\n5 - Random\n--> ";
	int opMode;

	while (!(std::cin >> opMode) || opMode < 1 || opMode > 5)
	{
		// Exit the program
		if (-1 == opMode)
		{
			return  -1;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid choice. Please enter a number between 1 and 5: ";
	}
	return opMode;
}
