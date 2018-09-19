#include <iostream>
#include <string>	
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();


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
	std::cout << "\nBULLS & COWS" << std::endl << std::endl;
	std::cout << "GUESS THE " << BCGame.GetHiddenWordLength();
	std::cout << " LETTER ISOGRAM" << std::endl << std::endl;

	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses while the game is NOT won
	// and there are still tries remaning
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); // TODO make loop checking valid

		// submit valid guess to the game, and receive counts
        FBCCount BCCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "\n" << "BULLS = " << BCCount.Bulls << "\n";
		std::cout << "COWS  = " << BCCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}


// loop until user gives valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::InvalidStatus;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 TotalTry = BCGame.GetMaxTries();
		std::cout << "TRY " << CurrentTry << "/" << TotalTry << std::endl << std::endl;
		std::cout << "ENTER YOUR GUESS: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckValid(Guess);
		switch (Status)
		{
		case EGuessStatus::WrongLength:
			std::cout << "\nERROR: PLEASE ENTER A " << BCGame.GetHiddenWordLength() << " LETTER WORD\n\n";
			break;
		case EGuessStatus::NotIsogram:
			std::cout << "\nERROR: PLEASE ENTER A WORD WITHOUT REPEATING LETTERS\n\n";
			break;
		case EGuessStatus::NotLowercase:
			std::cout << "\nERROR: PLEASE ENTER ALL LOWERCASE LETTERS\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // loop until no errors returned
	return Guess;
}


bool AskToPlayAgain()
{
	std::cout << "WOULD YOU LIKE TO PLAY AGAIN WITH THE SAME HIDDEN WORD? (Y/N) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "YOU WIN!\n\n";
	}
	else
	{
		std::cout << "YOU DIDN'T GET IT\n\n";
	}
	
	return;
}
