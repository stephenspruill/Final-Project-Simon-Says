from gpiozero import LED, Button
from time import sleep

ledG = LED(26)
ledR = LED(21)
ledB = LED(20)
ledY = LED(6)

butG = Button(22)
butR = Button(16)
butB = Button(12)
butY = Button(5)

# Startup sequence
ledG.on()
sleep(1)
ledG.off()
ledR.on()
sleep(1)
ledR.off()
ledB.on()
sleep(1)
ledB.off()
ledY.on()
sleep(1)
ledY.off()

While True:
    if butG.is_pressed:
        ledG.on()
        sleep(.1)
        ledG.off()

    elif butR.is_pressed:
        ledR.on()
        sleep(.1)
        ledR.off()

    elif butB.is_pressed:
        ledB.on()
        sleep(.1)
        ledB.off()

    elif butY.is_pressed:
        ledY.on()
        sleep(.1)
        ledY.off()
    
