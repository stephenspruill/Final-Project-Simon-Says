#include "functions.h"

void startUpSequence(){
    //output lights to flash
}

int generateRandomNum(){
    int randNum = 0;
    randNum = rand() % 3;
    return randNum
}

void outputSequenceTones(){
    //will need access to expected sequence
    for(int i = 0; i < /*size*/; i++){
        if(/*expectedSequence[i] == 0*/){
            //play sound for that certain button
        }else if (/*expectedSequence[i] == 1*/){
            //play sound for that certain button
        }else if (/*expectedSequence[i] == 2*/){
            //play sound for that certain button
        }else if (/*expectedSequence[i] == 3*/){
            //play sound for that certain button
        }
    }
}

bool checkIfUserCorrect(){
    //will need to access to both expected and user sequence
    bool result = false;

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

    return result;
}

void outputGameOver(){
    //play harsh tones

    if(/*difficulty == 0 && score > easyHighScore*/){
        /*easyHighScore = score*/
    }else if(/*difficulty == 1 && score > mediumHighScore*/){
        /*mediumHighScore = score*/
    }else if(/*difficulty == 2 && score > hardHighScore*/){
        /*hardHighScore = score*/
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
