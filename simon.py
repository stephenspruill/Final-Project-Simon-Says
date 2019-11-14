#import necessary libraries
import random
import time

#global variables
difficulty = 0
timer = 0.0
expectedSequence = []
userSequence = []

#global tracking variables
score = 0

easyHighScore = 0
mediumHighScore = 0
hardHighScore = 0

#main program
while(power is on):
    startUpSequence()
    wait_for_response() #from imported library, wait for start button to be pressed
    difficulty = #value from game board, from difficulty slider/button
    if(difficulty == 0): #easy difficulty
        determineTimerLength()
        count = 0
        
        bool continueGame = true #condition that is changed within the while if the sequences are not the same
        while(continueGame):
            #random num
            int num = generateRandNum()
            expectedSequence.append(num)

            #output expected sequence
            outputSequenceTones()
            secondCondition = True
            while count < len(expectedSequence) and secondCondition
                wait_for_response() #get user input

                if(userInput != expectedSequence[count]):
                    secondCondition = False
                else:
                    userSequence.append(userInput)
                    count+=1

            #checking if user is correct
            checkIfUserCorrect()
    elif(difficulty == 1):
        #copy paste code once finished implementing easy difficulty
    elif(difficulty == 2):
        #copy paste code once finished implementing other difficulties
    #if we want more difficulties we can add more; just adjust the timer within determineTimeAllowed()

#functions
def startUpSequence():
    #output lights to flash
    #setup any global variables
    #returns nothing

def generateRandNum():
    #generate a random num; will need rand library
    return random.randint(0,3)
    #returns an int (0-3)

def outputSequenceTones():
    for i in expectedSequence:
        #play sound for each signal
        if(i == 0):
            #play sound 1
        elif(i == 1):
            #play sound 2
        elif(i == 2):
            #play sound 3
        elif(i == 3):
            #play sound 4
        time.sleep(timer) #delay in between output of tones
    #returns nothing

def checkIfUserCorrect():
    #checking if user is correct
    if userSequence != expectedSequence:
        #user sequence does not match
        secondCondition = False
        outputGameOver(difficulty)
    else:
        #user sequence matches, increment score and clear user sequence
        print("Correct\n")
        score+=1
        userSequence.clear()

def outputGameOver():
    #will play harsh tones
    #handle any global variables to be reset
    #saving data into high score if score higher
    #maybe display their score and their high score for that difficulty

    #print high score
        if(difficulty == 0 and score > easyHighScore):            
            easyHighScore = score
        elif(difficulty == 1 and score > mediumHighScore):
            mediumHighScore = score
        elif(difficulty == 2 and score > hardHighScore):
            hardHighScore = score
        #print("\nHigh Score: " + str(highScore) + ", " + "Score: " + str(score))
        
        #determine if they want to continue or quit
        endInput = input("Try Again?(Y to continue, N to quit): ")
        if(endInput == "Y" or endInput == "y"):
            expectedSequence.clear()
            userSequence.clear()
            score = 0
        elif(endInput == "N" or endInput == "n"):
            condition = False
            print("\n\nEnd Program")
    #returns nothing

def determineTimerLength():
    if(difficulty == 0):
        timer = 3.0
    elif (difficulty == 1):
        timer = 1.5
    elif (difficulty == 2):
        timer = 0.5
    #returns nothing
