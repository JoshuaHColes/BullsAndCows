#include <iostream>
#include <string>	
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetGuess();
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
		FText Guess = GetGuess(); // TODO make loop checking valid

        EGuessStatus Status = BCGame.CheckValid(Guess);

		// submit valid guess to the game, and receive counts
        FBCCount BCCount = BCGame.SubmitGuess(Guess);

		// print number of bulls and cows
        std::cout << std::endl << "BULLS = " << BCCount.Bulls << std::endl;
        std::cout << "COWS  = " << BCCount.Cows << std::endl;

		std::cout << std::endl;
	}

	// TODO summarise game
}


FText GetGuess() // TODO change to GetValidGuess
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	int32 TotalTry = BCGame.GetMaxTries();

	// get a guess from the player
	std::cout << "TRY " << CurrentTry << "/" << TotalTry << std::endl << std::endl;
	std::cout << "ENTER YOUR GUESS: ";
	FText Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}


bool AskToPlayAgain()
{
	std::cout << "DO YOU WANT TO PLAY AGAIN? (Y/N) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
