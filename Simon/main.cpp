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
vector<int> easyHighSequence; //Need to read/write the *Sequence vectors from external file
vector<int> mediumHighSequence;
vector<int> hardHighSequence;

int main()
{
	//**********Variable Declaration*********
	int easyHighCount,  //Need to read/write the *Count values from external file
		mediumHighCount,
		hardHighCount,
		easyTempCount,
		mediumTempCount,
		hardTempCount;
	int timer1 = 500,
		timer2 = 200,
		timer3 = 25,
		gTone = 659,
		rTone = 440,
		bTone = 330,
		yTone = 554,
		selTone = 880;
	
	//**********Startup Sequence**********
	startUpSequence();

	//**********Mode Select Loop**********
	bool start = false;
	while (start == false)
	{
		//display current difficulty led (flashing?)
		//monitor difficulty select button and change difficulty as needed
		//monitor high sequence button and last button
		//monitor start button as exit from this while loop
		if(digitalRead(4) == 0) //check difficulty button
		{

		}
		if(digitalRead(24) == 0) //high sequence button
		{

		}
		if(digitalRead(23) == 0) //last button
		{

		}
		if(digitalRead(18) == 0) //start button
		{
			start = true;
		}
	}
	
	while (start == true)
	{
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

//**********LED and Sound Functions**********
void green(int time, int tone){
	system("/home/pi/code/LEDs/gon");
	softToneWrite(25, tone);
	delay(time);
	system("/home/pi/code/LEDs/gof");
	softToneWrite(25, 0);
}

void red(int time, int tone){
	system("/home/pi/code/LEDs/ron");
	softToneWrite(25, tone);
	delay(time);
	system("/home/pi/code/LEDs/rof");
	softToneWrite(25, 0);
}

void blue(int time, int tone){
	system("/home/pi/code/LEDs/bon");
	softToneWrite(25, tone);
	delay(time);
	system("/home/pi/code/LEDs/bof");
	softToneWrite(25, 0);
}

void yellow(int time, int tone){
	system("/home/pi/code/LEDs/yon");
	softToneWrite(25, tone);
	delay(time);
	system("/home/pi/code/LEDs/yof");
	softToneWrite(25, 0);
}

void easyLED(int time, int tone){
	system("/home/pi/code/LEDs/eon");
	softToneWrite(25, tone);
	delay(time);
	system("/home/pi/code/LEDs/eof");
	softToneWrite(25, 0);
}

void mediumLED(int time, int tone){
	system("/home/pi/code/LEDs/mon");
	softToneWrite(25, tone);
	delay(time);
	system("/home/pi/code/LEDs/mof");
	softToneWrite(25, 0);
}

void hardLED(int time, int tone){
	system("/home/pi/code/LEDs/hon");
	softToneWrite(25, tone);
	delay(time);
	system("/home/pi/code/LEDs/hof");
	softToneWrite(25, 0);
}

//**********Sequence Functions**********
void startUpSequence(){
	green(timer1, gtone);
	red(timer1, rtone);
	blue(timer1, btone);
	yellow(timer1, ytone);
	easyLED(timer1, selTone);
	mediumLED(timer1, selTone);
	hardLED(timer1, selTone);
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

