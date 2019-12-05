#include <iostream>
#include <iomanip>
#include <ctime>
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
vector<int> userHighest;

//Scoring Vectors
vector<int> easyHighSequence; //Need to read/write the *Sequence vectors from external file
vector<int> mediumHighSequence;
vector<int> hardHighSequence;
vector<int> high; //High sequence vector to reduce if loops when calling sequence vectors
vector<int> easyHighest;
vector<int> mediumHighest;
vector<int> hardHighest;
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
		readHighSequencesFromFile();
		//********** Mode Select Loop **********
		while (start == false)
		{
			
			//display current difficulty LED
			if(difficulty == 0 && pauseLoop == 0){
				easyLED(200, selTone);
				timer1 = 400;
				timer2 = 150;
				high = easyHighSequence;
				pauseLoop = 1;
			}
			if(difficulty == 1 && pauseLoop == 0){
				mediumLED(200, selTone);
				timer1 = 200;
				timer2 = 100;
				high = mediumHighSequence;
				pauseLoop = 1;
			}
			if(difficulty == 2 && pauseLoop == 0){
				hardLED(200, selTone);
				timer1 = 100;
				timer2 = 50;
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
				switch(difficulty)
				{
					case 0:
						outputSequence(easyHighest);
						break;
					case 1:
						outputSequence(mediumHighest);
						break;
					case 2:
						outputSequence(hardHighest);
						break;
				}
				delay(200);
			}
			if(digitalRead(18) == 0) //start button
			{
				start = true;
			}
		}
		
		//********** Gameplay Loop **********
		while(start)
		{
			    if(difficulty == 0 && userHighest.size() > easyHighSequence.size()) {
				updateEasyHighSequence();
				writeEasyHighSequenceToFile();
			    } else if (difficulty == 1 && userHighest.size() > mediumHighSequence.size()) {
				updateMediumHighSequence();
				writeMediumHighSequenceToFile();
			    } else if (difficulty == 2 && userHighest.size() > hardHighSequence.size()) {
				updateHardHighSequence();
				writeHardHighSequenceToFile();
			    }
			    switch(difficulty)
				{
					case 0:
						easyHighest = userSequence;
						break;
					case 1:
						mediumHighest = userSequence;
						break;
					case 2:
						hardHighest = userSequence;
						break;
				}
			expectedSequence.push_back(generateRandomNum());
			delay(timer2);
			outputSequence(expectedSequence);
			userSequence.clear();
			sequenceNum = 0;
			for(unsigned int i = 0; i < expectedSequence.size() && !userFail; i++)
			{
				while(!userChoice)
				{
					if(digitalRead(6) == 0)
					{
						green(timer1, gTone);
						userInput = 0;
						userChoice = true;
						delay(25);
					}
					if(digitalRead(16) == 0)
					{
						red(timer1, rTone);
						userInput = 1;
						userChoice = true;
						delay(25);
					}
					if(digitalRead(12) == 0)
					{
						blue(timer1, bTone);
						userInput = 2;
						userChoice = true;
						delay(25);
					}
					if(digitalRead(13) == 0)
					{
						yellow(timer1, yTone);
						userInput = 3;
						userChoice = true;
						delay(25);
					}
				}
					
					userChoice = false;
					userSequence.push_back(userInput);
					delay(timer2);
					if(userSequence[i] != expectedSequence[i])
					{
						userFail = true;
						userSequence.pop_back();
						sequenceNum++;
						break;
					}else
					{
						sequenceNum++;
						delay(200);
					}
				}
			
			
			if(userFail)
			{
				outputGameOver();
				start = false;
				userFail = false;
				sequenceNum = 0;
				pauseLoop = 0;
				
			}
			userHighest = userSequence;

		}	
		
	}
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
	hardLED(timer1, selTone);
	hardLEDoff();
	mediumLED(timer1, selTone);
	mediumLEDoff();
}

int generateRandomNum(){
    int randNum = 0;
    randNum = rand() % 4;
    return randNum;
}

//********** Output Sequence *********
void outputSequence(vector<int> &sequence){
    //will need access to expected sequence
    for(unsigned int i = 0; i < sequence.size(); i++){
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

    expectedSequence.clear();
}

void updateEasyHighSequence(){
    easyHighSequence = userHighest;
}

void updateMediumHighSequence(){
    mediumHighSequence = userHighest;
}

void updateHardHighSequence(){
    hardHighSequence = userHighest;
}

//********** Read/Write File **********

void writeEasyHighSequenceToFile() {
    //write out entire easy high sequence
    outFile.open(easyHighSequenceFileName);
    for (unsigned int i = 0; i < userHighest.size(); i++) {
        outFile << easyHighSequence[i] << ",";
    }
    outFile << endl;
    outFile.close();
    outFile.clear();
}

void writeMediumHighSequenceToFile() {
    //write out entire medium high sequence
    outFile.open(mediumHighSequenceFileName);
    for (unsigned int i = 0; i < userHighest.size(); i++) {
        outFile << mediumHighSequence[i] << ",";
    }
    outFile << endl;
    outFile.close();
    outFile.clear();
}

void writeHardHighSequenceToFile(){
    //write out entire hard high sequence
    outFile.open(hardHighSequenceFileName);
    for(unsigned int i = 0; i < userHighest.size(); i++){
        outFile << hardHighSequence[i] << ",";
    }
    outFile << endl;
    outFile.close();
    outFile.clear();
}

void readHighSequencesFromFile(){
    string line;
	easyHighSequence.clear();
	mediumHighSequence.clear();
	hardHighSequence.clear();
	high.clear();
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

