#include <iostream>
#include <string>	
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();


FBullCowGame BCGame; // instantiate a new game


// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; // exit the application
}


// introduce the game
void PrintIntro()
{
	std::cout << "BULLS & COWS" << std::endl << std::endl;
	std::cout << "GUESS THE " << BCGame.GetHiddenWordLength();
	std::cout << " LETTER ISOGRAM" << std::endl << std::endl;

	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
    for (int32 count = 1; count <= MaxTries; count++) // TODO change from FOR to WHILE
	{
		FText Guess = GetValidGuess(); // TODO make loop checking valid

		// submit valid guess to the game, and receive counts
        FBCCount BCCount = BCGame.SubmitGuess(Guess);

		std::cout << "\n" << "BULLS = " << BCCount.Bulls << "\n";
		std::cout << "COWS  = " << BCCount.Cows << "\n\n";
	}
	// TODO summarise game
}


// loop until user gives valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::InvalidStatus;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 TotalTry = BCGame.GetMaxTries();
		std::cout << "TRY " << CurrentTry << "/" << TotalTry << std::endl << std::endl;
		std::cout << "ENTER YOUR GUESS: ";
		FText Guess = "";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckValid(Guess);
		switch (Status)
		{
		case EGuessStatus::WrongLength:
			std::cout << "\nERROR: PLEASE ENTER A " << BCGame.GetHiddenWordLength() << " LETTER WORD\n";
			break;
		case EGuessStatus::NotIsogram:
			std::cout << "\nERROR: PLEASE ENTER A WORD WITHOUT REPEATING LETTERS\n";
			break;
		case EGuessStatus::NotLowercase:
			std::cout << "\nERROR: PLEASE ENTER ALL LOWERCASE LETTERS\n";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // loop until no errors returned
}


bool AskToPlayAgain()
{
	std::cout << "DO YOU WANT TO PLAY AGAIN? (Y/N) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
