#include <iostream>
#include <iomanip>
#include <ctime>
//#include "main.h"
#include <wiringPi.h>
#include <stdlib.h>
#include <softTone.h>
#include <time.h>
#include <fstream>
#include <vector>

using namespace std;

//Global Variables
int difficulty = 0;
int pauseLoop = 0;
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
	// ********** WiringPi input/tone setup **********
	wiringPiSetupGpio ();

	pinMode (6, INPUT);	//Green Button
	pinMode (16, INPUT);	//Red Button
	pinMode (12, INPUT);	//Blue Button
	pinMode (13, INPUT);	//Yellow Button
	pinMode (4, INPUT);	//Difficulty Button
	pinMode (18, INPUT);	//Start Button
	pinMode (23, INPUT);	//Last Button
	pinMode (24, INPUT);	//Longest Button
	softToneCreate (25);

	readHighSequencesFromFile();
	
	//********** Variable Declaration *********
	srand(time(0));		//Used to change the random seed during each startup
	/*int easyHighCount,  	//Need to read/write the *Count values from external file
		mediumHighCount,
		hardHighCount;*/
	int userInput;

	bool start = false;
	bool userChoice = false;

	//********** Startup Sequence **********
	system("/home/pi/code/LEDs/eof");
	system("/home/pi/code/LEDs/mof");
	system("/home/pi/code/LEDs/hof");
	startUpSequence();
	
	while (1)
	{
		//********** Mode Select Loop **********
		while (start == false)
		{
			//display current difficulty LED
			if(difficulty == 0 && pauseLoop == 0){
				easyLED(200, selTone);
				timer1 = 1000;
				timer2 = 400;
				high = easyHighSequence;
				pauseLoop = 1;
			}
			if(difficulty == 1 && pauseLoop == 0){
				mediumLED(200, selTone);
				timer1 = (timer1 * .5);
				timer2 = (timer2 * .5);
				high = mediumHighSequence;
				pauseLoop = 1;
			}
			if(difficulty == 2 && pauseLoop == 0){
				hardLED(200, selTone);
				timer1 = (timer1 * .5);
				timer2 = (timer2 * .5);
				high = hardHighSequence;
				pauseLoop = 1;
			}
			if(digitalRead(4) == 0) //check difficulty button
			{
				system("/home/pi/code/LEDs/eof");
				system("/home/pi/code/LEDs/mof");
				system("/home/pi/code/LEDs/hof");
				pauseLoop = 0;
				if (difficulty < 2){
					difficulty ++;
					delay(200);}
				else{
					difficulty = 0;
					delay(200);}
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
					if(digitalRead(6) == 0)
					{
						green(timer1, gTone);
						userInput = 0;
						cout << userInput << endl;
						userChoice = true;
					}
					if(digitalRead(16) == 0)
					{
						red(timer1, rTone);
						userInput = 1;
						cout << userInput << endl;
						userChoice = true;
					}
					if(digitalRead(12) == 0)
					{
						blue(timer1, bTone);
						userInput = 2;
						cout << userInput << endl;
						userChoice = true;
					}
					if(digitalRead(13) == 0)
					{
						yellow(timer1, yTone);
						userInput = 3;
						cout << userInput << endl;
						userChoice = true;
					}
					
					return userInput;
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
	softToneWrite(25, 0);
}

void easyLEDoff(){
	system("/home/pi/code/LEDs/eof");}

void mediumLED(int time, int tone){
	system("/home/pi/code/LEDs/mon");
	softToneWrite(25, tone);
	delay(time);
	softToneWrite(25, 0);
}

void mediumLEDoff(){
	system("/home/pi/code/LEDs/mof");}

void hardLED(int time, int tone){
	system("/home/pi/code/LEDs/hon");
	softToneWrite(25, tone);
	delay(time);
	softToneWrite(25, 0);
}

void hardLEDoff(){
	system("/home/pi/code/LEDs/hof");}

//********** Sequence Functions **********
void startUpSequence(){
	green(timer1, gTone);
	red(timer1, rTone);
	blue(timer1, bTone);
	yellow(timer1, yTone);
	easyLED(timer1, selTone);
	easyLEDoff();
	mediumLED(timer1, selTone);
	mediumLEDoff();
	hardLED(timer1, selTone);
	hardLEDoff();
}

int generateRandomNum(){
    int randNum = 0;
    randNum = rand() % 3;
    return randNum;
}

//********** Output Sequence *********
void outputSequence(vector<int> &sequence){
    //will need access to expected sequence
    for(unsigned int i = 0; i <= sequence.size(); i++){
	switch(sequence[i]){
		case 0:
			green(timer1, gTone);
			delay(timer2);
			break;
		case 1:
			red(timer1, rTone);
			delay(timer2);
			break;
		case 2:
			blue(timer1, bTone);
			delay(timer2);
			break;
		case 3:
			yellow(timer1, yTone);
			delay(timer2);
			break;
		}
    }
}

void outputGameOver()
{
 	for(int i=0;i<=20;i++)
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
        writeMediumHighSequenceToFile();
    } else if (difficulty == 2 && userSequence.size() > hardHighSequence.size()) {
        updateHardHighSequence();
        writeHardHighSequenceToFile();
    }
}

void updateEasyHighSequence(){
    easyHighSequence.clear();
    for(int i = 0; i < sequenceNum; i++){
        easyHighSequence.push_back(userSequence[i]);
    }
}

void updateMediumHighSequence(){
    mediumHighSequence.clear();
    for(int i = 0; i < sequenceNum; i++){
        mediumHighSequence.push_back(userSequence[i]);
    }
}

void updateHardHighSequence(){
    hardHighSequence.clear();
    for(int i = 0; i < sequenceNum; i++){
        hardHighSequence.push_back(userSequence[i]);
    }
}

//********** Read/Write File **********

void writeEasyHighSequenceToFile() {
    //write out entire easy high sequence
    outFile.open(easyHighSequenceFileName);
    for (int i = 0; i < sequenceNum; i++) {
        outFile << easyHighSequence[i] << ",";
    }
    outFile << endl;
    outFile.close();
    outFile.clear();
}

void writeMediumHighSequenceToFile() {
    //write out entire medium high sequence
    outFile.open(mediumHighSequenceFileName);
    for (int i = 0; i < sequenceNum; i++) {
        outFile << mediumHighSequence[i] << ",";
    }
    outFile << endl;
    outFile.close();
    outFile.clear();
}

void writeHardHighSequenceToFile(){
    //write out entire hard high sequence
    outFile.open(hardHighSequenceFileName);
    for(int i = 0; i < sequenceNum; i++){
        outFile << hardHighSequence[i] << ",";
    }
    outFile << endl;
    outFile.close();
    outFile.clear();
}

void readHighSequencesFromFile(){
    string line;

    inFile.open(easyHighSequenceFileName);
    while(getline(inFile, line, ',')){
        if(line[0] != '\n') {
            easyHighSequence.push_back(stoi(line));
        }
    }
    inFile.close();
    inFile.clear();

    inFile.open(mediumHighSequenceFileName);
    while(getline(inFile, line, ',')){
        if(line[0] != '\n') {
            mediumHighSequence.push_back(stoi(line));
        }
    }
    inFile.close();
    inFile.clear();

    inFile.open(hardHighSequenceFileName);
    while(getline(inFile, line, ',')){
        if(line[0] != '\n') {
            hardHighSequence.push_back(stoi(line));
        }
    }
    inFile.close();
    inFile.clear();
}
