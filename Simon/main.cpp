#include <iostream>
#include <iomanip>
#include <ctime>
#include "main.h"
#include <wiringPi.h>
#include <stdlib.h>
#include <softTone.h>

//Global Variables
int difficulty = 0;
int timer = 0.0;

//Main Vectors to Be Compared
vector<int> expectedSequence;
vector<int> userSequence;

//Scoring Vectors
int easyHighCount,
	mediumHighCount,
	hardHighCount;
vector<int> easyHighSequence;
vector<int> mediumHighSequence;
vector<int> hardHighSequence;

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
					
					if(!checkIfUserCorrect())
					{
						//user was not correct
						continueGame = false;
					}
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

void startUpSequence(){
    //output lights to flash
}

int generateRandomNum(){
    int randNum = 0;
    randNum = rand() % 3;
    return randNum
}

void outputSequenceTones(){
    //will need access to expected sequence
    for(int i = 0; i < /*size*/; i++){
        if(/*expectedSequence[i] == 0*/){
            //play sound for that certain button
        }else if (/*expectedSequence[i] == 1*/){
            //play sound for that certain button
        }else if (/*expectedSequence[i] == 2*/){
            //play sound for that certain button
        }else if (/*expectedSequence[i] == 3*/){
            //play sound for that certain button
        }
    }
}

bool checkIfUserCorrect(){
    bool wasUserCorrect = true;
    for(int i = 0; i < /*size*/ && wasUserCorrect; i++){
        if(/*expectedSequence[i] != userSequence[i]*/){
            //user incorrect
            wasUserCorrect = false;
            outputGameOver();
        } else {
            //user was correct
            /*score++*/
            /*userSequence.clear()*/
        }
    }
	return wasUserCorrect;
}

void outputGameOver(){
    //play harsh tones

    if(/*difficulty == 0 && score > easyHighScore*/){
        /*easyHighScore = score*/
    }else if(/*difficulty == 1 && score > mediumHighScore*/){
        /*mediumHighScore = score*/
    }else if(/*difficulty == 2 && score > hardHighScore*/){
        /*hardHighScore = score*/
    }
}

void determineTimerLength(){
    if(/*difficulty == 0*/){
        /*timer = 3.0*/
    }else if(/*difficulty == 1*/){
        /*timer = 1.5*/
    }else if(/*difficulty == 2*/){
        /*timer = 0.5*/
    }
}

