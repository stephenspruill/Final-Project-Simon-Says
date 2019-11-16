#ifndef SIMON_FUNCTIONS_H
#define SIMON_FUNCTIONS_H

#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

void startUpSequence();
int generateRandomNum();
void outputSequenceTones();
bool checkIfUserCorrect();
void outputGameOver();
void determineTimerLength();

#endif //SIMON_FUNCTIONS_H
