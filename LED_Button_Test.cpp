#include <iostream>
#include <wiringPi.h>

using namespace std;

int main ()
{
	wiringPiSetup ();
	pinMode (26, OUTPUT);
	pinMode (21, OUTPUT);
	pinMode (20, OUTPUT);
	pinMode (19, OUTPUT);
	
	pinMode (6, INPUT);
	pinMode (16, INPUT);
	pinMode (12, INPUT);
	pinMode (13, INPUT);


	while(1)
	{
		if(digitalRead(6) == 1)
		{
		digitalWrite (26, !digitalRead(26));
		delay (500);
		}
		elif(digitalRead(16) == 1)
		{
		digitalWrite (21, !digitalRead(21));
		delay (500);
		}
		elif(digitalRead(12) == 1)
		{
		digitalWrite (20, !digitalRead(20));
		delay (500);
		}		
		elif(digitalRead(13) == 1)
		{
		digitalWrite (19, !digitalRead(19));
		delay (500);
		}
	}
	return 0;
}
