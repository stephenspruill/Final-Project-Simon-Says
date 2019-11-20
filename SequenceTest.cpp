// to compile, run the following in terminal
//g++ -std=c++0x SequenceTest.cpp -otest -lwiringPi -lpthread
//sudo ./test

#include <iostream>
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <softTone.h>

using namespace std;

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
					delay(200);
					digitalWrite (26, HIGH);
					softToneWrite(25, 659);
					delay(500);
					digitalWrite (26, LOW);
					softToneWrite(25, 0);
					break;
				case 1:
					delay(200);
					digitalWrite (21, HIGH);
					softToneWrite(25, 440);
					delay(500);
					digitalWrite (21, LOW);
					softToneWrite(25, 0);
					break;
				case 2:
					delay(200);
					digitalWrite (20, HIGH);
					softToneWrite(25, 330);
					delay(500);
					digitalWrite (20, LOW);
					softToneWrite(25, 0);
					break;
				case 3:
					delay(200);
					digitalWrite (19, HIGH);
					softToneWrite(25, 554);
					delay(500);
					digitalWrite (19, LOW);
					softToneWrite(25, 0);
					break;
			}
		}
			
		cout << "\nMake your guess!" << endl;
		cout << "Debug: Displaying user's choice" << endl << endl;
		for(int i = 0; i <= sequenceNum && !userFail; i++)
		{
			while(!userChoice)
			{
				if(digitalRead(6) == 0)
				{
					digitalWrite (26, HIGH);
					softToneWrite(25, 659);
					delay(500);
					digitalWrite (26, LOW);
					softToneWrite(25, 0);
					userInput = 0;
					cout << userInput << endl;
					userChoice = true;
				}
				if(digitalRead(16) == 0)
				{
					digitalWrite (21, HIGH);
					softToneWrite(25, 440);
					delay(500);
					digitalWrite (21, LOW);
					softToneWrite(25, 0);
					userInput = 1;
					cout << userInput << endl;
					userChoice = true;
				}
				if(digitalRead(12) == 0)
				{
					digitalWrite (20, HIGH);
					softToneWrite(25, 330);
					delay(500);
					digitalWrite (20, LOW);
					softToneWrite(25, 0);
					userInput = 2;
					cout << userInput << endl;
					userChoice = true;
				}
				if(digitalRead(13) == 0)
				{
					digitalWrite (19, HIGH);
					softToneWrite(25, 554);
					delay(500);
					digitalWrite (19, LOW);
					softToneWrite(25, 0);
					userInput = 3;
					cout << userInput << endl;
					userChoice = true;
				}
				
			}
				userChoice = false;
				userSeq.push_back(userInput);
				cout << "\nDebug: Comparing your input of " << userSeq[i]
					 << " with sequence input of " << seq[i] << endl;
				delay(500);
				if(userSeq[i] != seq[i])
				{
					cout << "Incorrect!" << endl;
					for(i=0;i<=20;i++)
					{
						digitalWrite (26, HIGH);
						digitalWrite (20, HIGH);
						softToneWrite(25, 150);
						delay(25);
						digitalWrite (26, LOW);
						digitalWrite (20, LOW);
						digitalWrite (21, HIGH);
						digitalWrite (19, HIGH);												
						softToneWrite(25, 75);
						delay(25);
						digitalWrite (21, LOW);
						digitalWrite (19, LOW);
						digitalWrite (26, HIGH);
						digitalWrite (20, HIGH);						
						softToneWrite(25, 125);
						delay(25);
						digitalWrite (26, LOW);
						digitalWrite (20, LOW);
						digitalWrite (21, HIGH);
						digitalWrite (19, HIGH);						
						softToneWrite(25, 50);
						delay(25);
						digitalWrite (21, LOW);
						digitalWrite (19, LOW);					
					}
					userFail = true;
					break;
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
