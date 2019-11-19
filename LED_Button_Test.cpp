// to compile, run the following in terminal
//g++ -std=c++0x btest.cpp -obtest -lwiringPi
#include <iostream>
#include <stdio.h>
#include <wiringPi.h>

using namespace std;

int main()
{
	wiringPiSetupGpio ();
	
	pinMode (26, OUTPUT);	//Green LED
	pinMode (21, OUTPUT);	//Red LED
	pinMode (20, OUTPUT);	//Blue LED
	pinMode (19, OUTPUT);	//Yellow LED
	
	pinMode (6, INPUT);		//Green Button
	pinMode (4, INPUT);		//Red Button
	pinMode (12, INPUT);	//Blue Button
	pinMode (13, INPUT);	//Yellow Button

	digitalWrite (26, LOW);
	digitalWrite (21, LOW);
	digitalWrite (20, LOW);
	digitalWrite (19, LOW);
	
	while(1)
	{
		if(digitalRead(6) == 0)	//green
		{
			cout << "Green on" << endl;
			digitalWrite(26, HIGH);
			delay (500);
			digitalWrite (26, LOW);
		}
		if(digitalRead(4) == 0)	//red
		{
			cout << "Red on" << endl;
			digitalWrite(21, HIGH);
			delay (500);
			digitalWrite (21, LOW);
		}
		if(digitalRead(13) == 0)	//yellow
		{
			cout << "Yellow on" << endl;
			digitalWrite(19, HIGH);
			delay (500);
			digitalWrite (19, LOW);
		}
		if(digitalRead(12) == 0)	//blue
		{
			cout << "Blue on" << endl;
			digitalWrite(20, HIGH);
			delay (500);
			digitalWrite (20, LOW);
		}
	}

	return 0;
}
