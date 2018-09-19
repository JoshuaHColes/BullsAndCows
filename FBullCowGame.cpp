#include "FBullCowGame.h"


using int32 = int;


FBullCowGame::FBullCowGame() { Reset(); }


int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }


void FBullCowGame::Reset()
{
    constexpr int32 MaxTries = 5;
    const FString HiddenWord = "planet";

    MyMaxTries = MaxTries;
    MyHiddenWord = HiddenWord;
    MyCurrentTry = 1;
	return;
}


bool FBullCowGame::IsGameWon() const
{
	return false;
}


EGuessStatus FBullCowGame::CheckValid(FString Guess) const
{
    // if the guess isn't an isogram
    if (false)
    {
        return EGuessStatus::NotIsogram;
    }
    // if the guess isn't all lowercase
    else if (false)
    {
        return EGuessStatus::NotLowercase;
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
        EGuessStatus::OK;
    }
}


// receives a VALID guess, incriments turn, and returns count
FBCCount FBullCowGame::SubmitGuess(FString Guess)
{
	// incriment the turn number
	MyCurrentTry++;

	// setup a return variable
    FBCCount BCCount;

	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
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

    return BCCount;
}
