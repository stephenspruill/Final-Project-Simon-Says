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
vector<int> high; //High sequence vector to reduce if loops when calling sequence vectors


int main()
{
	//**********Variable Declaration*********
	int easyHighCount,  //Need to read/write the *Count values from external file
		mediumHighCount,
		hardHighCount;
	int timer1 = 500,
		timer2 = 200,
		timer3 = 25,
		gTone = 659,
		rTone = 440,
		bTone = 330,
		yTone = 554,
		selTone = 880;
	bool start = false;

	//**********Startup Sequence**********
	startUpSequence();
	
	while (1)
	{
		//**********Mode Select Loop**********
		while (start == false)
		{
			//display current difficulty LED
			if(difficulty == 0){
				system("/home/pi/code/LEDs/eon");
				
			}
			if(difficulty == 1){
				system("/home/pi/code/LEDs/mon");
			}
			if(difficulty == 2){
				system("/home/pi/code/LEDs/hon");
			}
			if(digitalRead(4) == 0) //check difficulty button
			{
				system("/home/pi/code/LEDs/eof");
				system("/home/pi/code/LEDs/mof");
				system("/home/pi/code/LEDs/hof");
				if (difficulty <= 2)
					difficulty ++;
				else
					difficulty = 0;
			}
			if(digitalRead(24) == 0) //high sequence button
			{
				if (difficulty == 0)
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
}

void mediumLED(int time, int tone){
	system("/home/pi/code/LEDs/mon");
	softToneWrite(25, tone);
	delay(time);
}

void hardLED(int time, int tone){
	system("/home/pi/code/LEDs/hon");
	softToneWrite(25, tone);
	delay(time);
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

void outputSequence(vector<int> &sequence){
    //will need access to expected sequence
    for(int i = 0; i < sequence.size(); i++){
	switch(sequence[i]){
		case 0:
			green(timer1, gtone);
			delay(timer2);
			break;
		case 1:
			red(timer1, rtone);
			delay(timer2);
			break;
		case 2:
			blue(timer1, btone);
			delay(timer2);
			break;
		case 3:
			yellow(timer1, ytone);
			delay(timer2);
			break;
	}
        /*if(sequence[i] == 0){
            green(timer1, gtone);
        }else if (sequence[i] == 1){
            red(timer1, rtone);
        }else if (sequence[i] == 2){
            blue(timer1, btone);
        }else if (sequence[i] == 3){
            yellow(timer1, ytone);
        }*/
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

