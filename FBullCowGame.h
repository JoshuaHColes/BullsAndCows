#pragma once
#include <string>


using FString = std::string;
using int32 = int;


// all values intialised to zero
struct FBCCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};


enum EGuessStatus
{
	InvalidStatus,
	OK,
	NotIsogram,
	WrongLength,
	NotLowercase
};


class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
    EGuessStatus CheckValid(FString) const;

	void Reset(); // TODO make a more rich return value.
    FBCCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
};
