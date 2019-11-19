#include <iostream>
#include <iomanip>
#include <ctime>
#include "main.h"
using namespace std;

int difficulty = 0;
int timer = 0.0;
vector<int> expectedSequence;
vector<int> userSequence;
vector<int> easyHighSequence;
vector<int> mediumHighSequence;
vector<int> hardHighSequence;


//global tracking variables
int score = 0;

int easyHighScore = 0;
int mediumHighScore = 0;
int hardHighScore = 0;



int main()
{
	bool power = true;
	while (power == true)
	{
		startUpSequence();
		waitForResponse();
		difficulty = // value from game board, from difficulty slider/button
		if (difficulty == 0) // easy difficulty
		{
			determineTimerLength();
			int count = 0;
		
		
			bool continueGame = true;
			while (continueGame == true)
			{
				int num = generateRandomNum();
				expectedSequence.push_back(num);
			
				outputSequenceTones();
				result = true;
				while (count < expectedSequence.size() && result)
				{
					waitForResponse();
				
					if(userInput != expectedSequence[count])
					{
						result = false;
					}
					else
					{
						userSequence.push_back(userInput);
						count++;
					}
				checkIfUserCorrect();
		
				
				}
			}
		else if( difficulty == 1)
		{
			//copy paste code once finished implementing easy difficulty
		}
		else if(difficulty == 2)
		{
			//copy paste code once finished implementing easy difficulty
		}
		}
	}
	
	
	
	
}
