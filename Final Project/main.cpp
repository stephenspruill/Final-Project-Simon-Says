#include <iostream>
#include <iomanip>
#include<ctime>
#include <wiringPi.h>
#include <stdlib.h>
#include <softTone.h>
#include <time.h>
#include <fstream>
#include <vector>

using namespace std;

//Global Variables
int difficulty = 0;int pauseLoop = 0;
int sequenceNum = 0;
bool userFail = false;
int timer1 = 500,
	timer2 = 200,
	timer3 = 25,
	gTone = 659,
	rTone = 440,
	bTone = 330,
	yTone = 554,
	selTone = 880;

// ********** Function Prototypes **********
void green(int, int);
void red(int, int);
void blue(int, int);
void yellow(int, int);
void easyLED(int, int);
void mediumLED(int, int);
void hardLED(int, int);
void easyLEDoff();
void mediumLEDoff();
void hardLEDoff();

void startUpSequence();
int generateRandomNum();
void outputSequence(vector<int> &);
void outputGameOver();
void updateEasyHighSequence();
void updateMediumHighSequence();
void updateHardHighSequence();

void writeEasyHighSequenceToFile();
void writeMediumHighSequenceToFile();
void writeHardHighSequenceToFile();
void readHighSequencesFromFile();
#include <iostream>
#include <iomanip>
