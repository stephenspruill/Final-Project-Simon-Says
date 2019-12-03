// to compile, run the following in terminal
//g++ -std=c++0x btest.cpp -obtest -lwiringPi -lpthread
//sudo ./test

#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <softTone.h>

using namespace std;

//functionprototypes
void green(int, int);
void red(int, int);
void blue(int, int);
void yellow(int, int);

int main()
{
	wiringPiSetupGpio ();
	
	pinMode (26, OUTPUT);	//Green LED
	pinMode (21, OUTPUT);	//Red LED
	pinMode (20, OUTPUT);	//Blue LED
	pinMode (19, OUTPUT);	//Yellow LED
	
	pinMode (6, INPUT);		//Green Button
	pinMode (16, INPUT);		//Red Button
	pinMode (12, INPUT);	//Blue Button
	pinMode (13, INPUT);	//Yellow Button
	
	softToneCreate (25);

	digitalWrite (26, LOW);
	digitalWrite (21, LOW);
	digitalWrite (20, LOW);
	digitalWrite (19, LOW);
	
	srand(time(0));
	bool gameOver = false;
	bool userFail = false;
	bool userChoice = false;
	int sequenceNum = 0;
	int randNum = 0;
	int userInput = 0;
	vector<int> seq;
	vector<int> userSeq;
	int timer1 = 500;
	int timer2 = 200;
	int timer3 = 25;
	int gtone = 659;
	int rtone = 440;
	int btone = 330;
	int ytone = 554;
	
	while(!gameOver)
	{
		cout << "Generating sequence..." << endl << endl;
		randNum = rand() % 3;
		seq.push_back(randNum);
		delay(500);
		for(int i = 0; i <= sequenceNum; i++)
		{
			cout << "Debug: Sequence is: " << seq[i] << endl;
		}
		for(int i = 0; i <= sequenceNum; i++)
		{
			switch(seq[i])
			{
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
		}
			
		cout << "\nMake your guess!" << endl;
		cout << "Debug: Displaying user's choice" << endl << endl;
		for(int i = 0; i <= sequenceNum && !userFail; i++)
		{
			while(!userChoice)
			{
				digitalRead();
			}
				userChoice = false;
				userSeq.push_back(userInput);
				cout << "\nDebug: Comparing your input of " << userSeq[i]
					 << " with sequence input of " << seq[i] << endl;
				delay(500);
				if(userSeq[i] != seq[i])
				{
					notEqual();
				}else
				{
					cout << "Correct!" << endl;
				}
		}
		if(userFail)
		{
			cout << "Game Over!" << endl;
			gameOver = true;
		}
		userSeq.clear();
		sequenceNum++;
	}
	cout << "Thanks for playing!" << endl;
	return 0;
}

// functions
void green(int time, int tone)
{
	system("/home/pi/code/LEDs/gon");
	softToneWrite(25, tone);
	delay(time);
	system("/home/pi/code/LEDs/gof");
	softToneWrite(25, 0);
}

void red(int time, int tone)
{
	system("/home/pi/code/LEDs/ron");
	softToneWrite(25, tone);
	delay(time);
	system("/home/pi/code/LEDs/rof");
	softToneWrite(25, 0);
}

void blue(int time, int tone)
{
	system("/home/pi/code/LEDs/bon");
	softToneWrite(25, tone);
	delay(time);
	system("/home/pi/code/LEDs/bof");
	softToneWrite(25, 0);
}

void yellow(int time, int tone)
{
	system("/home/pi/code/LEDs/yon");
	softToneWrite(25, tone);
	delay(time);
	system("/home/pi/code/LEDs/yof");
	softToneWrite(25, 0);
}
void digitalRead()
{
	if(digitalRead(6) == 0)
	{
		green(timer1, gtone);
		userInput = 0;
		cout << userInput << endl;
		userChoice = true;
	}
	if(digitalRead(16) == 0)
	{
		red(timer1, rtone);
		userInput = 1;
		cout << userInput << endl;
		userChoice = true;
	}
	if(digitalRead(12) == 0)
	{
		blue(timer1, btone);
		userInput = 2;
		cout << userInput << endl;
		userChoice = true;
	}
	if(digitalRead(13) == 0)
	{
		yellow(timer1, ytone);
		userInput = 3;
		cout << userInput << endl;
		userChoice = true;
	}
				
}
void notEqual()
{
	cout << "Incorrect!" << endl;
	for(i=0;i<=20;i++)
	{
		green(timer3, 150);
		red(timer3, 75);
		blue(timer3, 125);
		yellow(timer3, 50);					
	}
	userFail = true;
	break;
}
