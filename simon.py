#import necessary libaries

#global variables
int difficulty = 0
expectedSequence = []
userSequence = []

#global tracking variables
int score

int easyHighScore
int mediumHighScore
int hardHighScore

#main program
while(power is on):
    startUpSequence()
    wait_for_response() #from imported library, wait for start button to be pressed
    difficulty = #value from game board, from difficulty slider/button
    if(difficulty == 0): #easy difficulty
        int timeAllowed = determineTimeAllowed(difficulty)
        #to be used to compare if user took longer or shorter than the allowed time
        #(or if imported functions have the ability to set the time allowed for a response)
        bool continueGame = true #condition that is changed within the while if the sequences are not the same
        while(continueGame):
            int num = generateRandNum()
            expectedSequence.append(num)
            outputSequenceTones()
            #start timer
            wait_for_response()
            #stop timer
            #compare time length with timeAllowed #if less than timeAllowed; check sequence #else greater than timeAllowed; gameOver
            #append userSequence with what button was pressed; based on input
            if(expectedSequence != userSequence):
                continueGame = false
        outputGameOver()
    elif(difficulty == 1):
        #copy paste code once finished implementing easy difficulty
        #not necssary, difficulty will just alter a global timer variable
    elif(difficulty == 2):
        #copy paste code once finished implementing other difficulties
    #if we want more difficulties we can add more; just adjust the times within determineTimeAllowed()

#functions
def startUpSequence():
    #output lights to flash
    #setup any global variables
    #returns nothing

def generateRandNum():
    #generate a random num; will need rand library
    #returns an int 0-3

def outputSequenceTones():
    for i in expectedSequence:
        #play sound for each signal
        #likely need to set 0-3 to play a certain signal
    #returns nothing

def outputGameOver():
    #will play harsh tones
    #handle any global variables to be reset
    #saving data into high score if score higher
    #maybe display their score and their high score for that difficulty
    #returns nothing

def determineTimeAllowed(int difficulty):
    # difficulty will change delay between output instances making the 
    # output sequece faster for higher difficulty
    if(difficulty == 0):
        #time allowed should be for example 5 seconds
    elif (difficulty == 1):
        #time allowed should be for example 3 seconds
    elif (difficulty == 2):
        #time allowed should be for example 1.5 seconds

    #returns the time that should be allowed




        
