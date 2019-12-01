#ifndef SIMON_MAIN_H
#define SIMON_MAIN_H

#include <iostream>
using namespace std;

//Main Functions
void startUpSequence();
int generateRandomNum();
void outputSequenceTones();
bool checkIfUserCorrect();
void outputGameOver();
void determineTimerLength();

//LED and Sound Functions
void green(int, int);
void red(int, int);
void blue(int, int);
void yellow(int, int);
void easyLED(int, int);
void mediumLED(int, int);
void hardLED(int, int);

#endif //SIMON_MAIN_H
