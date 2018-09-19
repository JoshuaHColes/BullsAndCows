#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }


int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


void FBullCowGame::Reset()
{
	constexpr int32 MaxTries = 5;
	const FString HiddenWord = "planet";

	MyMaxTries = MaxTries;
	MyHiddenWord = HiddenWord;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckValid(FString Guess) const
{
	// if the guess isn't an isogram
	if (false)
	{
		return EGuessStatus::NotIsogram; // TODO write function
	}
	// if the guess isn't all lowercase
	else if (false)
	{
		return EGuessStatus::NotLowercase; // TODO write function
	}
	// if guess length is wrong
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::WrongLength;
	}
	// otherwise
	else
	{
		// return OK
		return EGuessStatus::OK;
	}
}


// receives a VALID guess, incriments turn, and returns count
FBCCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBCCount BCCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same word as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{ // if they're in the same place
					BCCount.Bulls++; // incriment bulls
				}
				else
				{
					BCCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BCCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BCCount;
}
