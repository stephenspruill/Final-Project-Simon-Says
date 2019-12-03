#include <iostream>
#include <iomanip>
#include <ctime>
#include "main.h"
#include <wiringPi.h>
#include <stdlib.h>
#include <softTone.h>
#include <time.h>
#include <fstream>

using namespace std;

//********** Function Prototypes **********
void green(int, int);
void red(int, int);
void blue(int, int);
void yellow(int, int);
void easyLED(int, int);
void mediumLED(int, int);
void hardLED(int, int);

void startUpSequence();
int generateRandomNum();
void outputSequence(vector<int> &);
bool checkIfUserCorrect();
void outputGameOver();
void determineTimerLength();
void getUserInput()
void updateEasyHighSequence();
void updateMediumHighSequence();
void updateHardHighSequence();

void writeEasyHighSequenceToFile();
void writeMediumHighSequenceToFile();
void writeHardHighSequenceToFile();
void readHighSequencesFromFile();

//********** WiringPi input/tone setup **********
wiringPiSetupGpio ();
pinMode (6, INPUT);	//Green Button
pinMode (16, INPUT);	//Red Button
pinMode (12, INPUT);	//Blue Button
pinMode (13, INPUT);	//Yellow Button
softToneCreate (25);

//Global Variables
int difficulty = 0;
int sequenceNum = 0;
bool userFail = false;

//Main Vectors to Be Compared
vector<int> expectedSequence;
vector<int> userSequence;

//Scoring Vectors
vector<int> easyHighSequence; //Need to read/write the *Sequence vectors from external file
vector<int> mediumHighSequence;
vector<int> hardHighSequence;
vector<int> high; //High sequence vector to reduce if loops when calling sequence vectors

//Read/Write File
ifstream inFile;
ofstream outFile;

string easyHighSequenceFileName = "easyHighSequence.csv";
string mediumHighSequenceFileName = "mediumHighSequence.csv";
string hardHighSequenceFileName = "hardHighSequence.csv";

int main()
{
	readHighScoreSequencesFromFile();
	
	//********** Variable Declaration *********
	srand(time(0));		//Used to change the random seed during each startup
	int easyHighCount,  	//Need to read/write the *Count values from external file
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

	//********** Startup Sequence **********
	startUpSequence();
	
	while (1)
	{
		//********** Mode Select Loop **********
		while (start == false)
		{
			//display current difficulty LED
			if(difficulty == 0){
				system("/home/pi/code/LEDs/eon");
				timer1 = 1000,
				timer2 = 400;
				high = easyHighSequence;
			}
			if(difficulty == 1){
				system("/home/pi/code/LEDs/mon");
				timer1 = (timer1 * .5);
				timer2 = (timer2 * .5);
				high = mediumHighSequence;
			}
			if(difficulty == 2){
				system("/home/pi/code/LEDs/hon");
				timer1 = (timer1 * .5);
				timer2 = (timer2 * .5);
				high = hardHighSequence;
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
				outputSequence(high);
			}
			if(digitalRead(23) == 0) //last button
			{
				outputSequence(userSequence);
			}
			if(digitalRead(18) == 0) //start button
			{
				start = true;
			}
		}
		
		//********** Gameplay Loop **********
		while(start)
		{
			cout << "Generating sequence..." << endl << endl;
			expectedSequence.push_back(generateRandomNum());
			delay(timer2);
			for(int i = 0; i <= sequenceNum; i++)
			{
				cout << "Debug: Sequence is: " << expectedSequence[i] << endl;
			}
			outputSequence(expectedSequence);
			
			cout << "\nMake your guess!" << endl;
			cout << "Debug: Displaying user's choice" << endl << endl;
			for(int i = 0; i <= sequenceNum && !userFail; i++)
			{
				while(!userChoice)
				{
					getUserInput();
				}
					userChoice = false;
					userSequence.push_back(userInput);
					cout << "\nDebug: Comparing your input of " << userSequence[i]
						 << " with sequence input of " << expectedSequence[i] << endl;
					delay(timer2);
					if(userSequence[i] != expectedSequence[i])
					{
						userFail = true;
						cout << "Incorrect!" << endl;
						break;
					}else
					{
						cout << "Correct!" << endl;
					}
				}
			}
			
			if(userFail)
			{
				outputGameOver();
				cout << "Game Over!" << endl;
				start = false;
			}
			userSequence.clear();
			sequenceNum++;
		}	
		sequenceNum = 0;
	}

//********** LED and Sound Functions **********
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

//********** Sequence Functions **********
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

//********** Output Sequence *********
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

void outputGameOver()
{
 	for(i=0;i<=20;i++)
	{
		green(timer3, 150);
		red(timer3, 75);
		blue(timer3, 125);
		yellow(timer3, 50);					
	}
    if(difficulty == 0 && userSequence.size() > easyHighSequence.size()) {
        updateEasyHighSequence();
        writeEasyHighSequenceToFile();
    } else if (difficulty == 1 && userSequence.size() > mediumHighSequence.size()) {
        updateMediumHighSequence();
        writeMediumHighSequencesToFile();
    } else if (difficulty == 2 && userSequence.size() > hardHighSequence.size()) {
        updateHardHighSequence();
        writeHardHighSequencesToFile();
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

void getUserInput()
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

void updateEasyHighSequence(){
    easyHighSequence.clear();
    for(int i = 0; i < userSequence.size(); i++){
        easyHighSequence.push_back(userSequence[i]);
    }
}

void updateMediumHighSequence(){
    mediumHighSequence.clear();
    for(int i = 0; i < userSequence.size(); i++){
        mediumHighSequence.push_back(userSequence[i]);
    }
}

void updateHardHighSequence(){
    hardHighSequence.clear();
    for(int i = 0; i < userSequence.size(); i++){
        hardHighSequence.push_back(userSequence[i]);
    }
}

//********** Read/Write File **********

void writeEasyHighSequenceToFile() {
    //write out entire easy high sequence
    outFile.open(easyHighSequenceFileName);
    for (int i = 0; i < easyHighSequence.size(); i++) {
        outFile << easyHighSequence[i] << ",";
    }
    outFile << endl;
    outFile.close();
    outFile.clear();
}

void writeMediumHighSequenceToFile() {
    //write out entire medium high sequence
    outFile.open(mediumHighSequenceFileName)
    for (int i = 0; i < mediumHighSequence.size(); i++) {
        outFile << mediumHighSequence[i] << ",";
    }
    outFile << endl;
    outFile.close();
    outFile.clear();
}

void writeHardHighSequenceToFile(){
    //write out entire hard high sequence
    outFile.open(hardHighSequenceFileName)
    for(int i = 0; i < hardHighSequence.size(); i++){
        outFile << hardHighSequence[i] << ",";
    }
    outFile << endl;
    outFile.close();
    outFile.clear();
}

void readHighSequencesFromFile(){
    string line;
    int i;

    inFile.open(easyHighSequenceFileName);
    getLine(inFile, line, '\n');
    if(line.size() > 0) {
        easyHighSequence.clear();
        i = 0;
        while (line[i] != '\n') {
            if (line[i] != ',') {
                easyHighSequence[i].push_back(line[i]);
                i++;
            } else {
                i++;
            }
        }
        inFile.close();
        inFile.clear();
    }

    inFile.open(mediumHighSequenceFileName);
    getLine(readMediumHighSequence, line, '\n');
    if(line.size() > 0) {
        mediumHighSequence.clear();
        i = 0;
        while (line[i] != '\n') {
            if (line[i] != ',') {
                mediumHighSequence[i].push_back(line[i]);
                i++;
            } else {
                i++;
            }
        }
        inFile.close();
        inFile.clear();
    }

    inFile.open(hardHighSequenceFileName);
    getLine(readHardHighSequence, line, '\n');
    if(line.size() > 0) {
        hardHighSequence.clear();
        i = 0;
        while (line[i] != '\n') {
            if (line[i] != ',') {
                hardHighSequence[i].push_back(line[i]);
                i++;
            } else {
                i++;
            }
        }
        inFile.close();
        inFile.clear();
    }
}
