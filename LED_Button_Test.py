from gpiozero import LED, Button, TonalBuzzer
from gpiozero.tones import Tone
from time import sleep



ledG = LED(26)
ledR = LED(21)
ledB = LED(20)
ledY = LED(19)

butG = Button(6)
butR = Button(16)
butB = Button(12)
butY = Button(13)

bz = TonalBuzzer(25)

time1 = 0.1
time2 = 0.05
time3 = 0.025

# define output functions
def green(time):
    ledG.on()
    bz.play(Tone(659.255))
    sleep(time)
    ledG.off()
    sleep(time)
    bz.stop()
    return;

def red(time):
    ledR.on()
    bz.play(Tone(440))
    sleep(time)
    ledR.off()
    sleep(time)
    bz.stop()
    return;

def blue(time):
    ledB.on()
    bz.play(Tone(329.628))
    sleep(time)
    ledB.off()
    sleep(time)
    bz.stop()    
    return;

def yellow(time):
    ledY.on()
    bz.play(Tone(554.365))
    sleep(time)
    ledY.off()
    sleep(time)
    bz.stop()
    return;

def fail():
    i=0
    while (i<=15):
        blue(time3)
        green(time3)
        yellow(time3)
        red(time3)
        i=i+1    

# Startup sequence
green(time1)
red(time1)
blue(time1)
yellow(time1)
green(time2)
red(time2)
blue(time2)
yellow(time2)

fail()
    

while True:
    if butG.is_pressed:
        green(time1)

    elif butR.is_pressed:
        red(time1)

    elif butB.is_pressed:
        blue(time1)
        
    elif butY.is_pressed:
        yellow(time1)
