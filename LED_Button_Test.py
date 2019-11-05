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
    butG.wait_for_press()
    ledG.on()
    sleep(.1)
    ledG.off()

    butR.wait_for_press()
    ledR.on()
    sleep(.1)
    ledR.off()

    butB.wait_for_press()
    ledB.on()
    sleep(.1)
    ledB.off()

    butY.wait_for_press()
    ledY.on()
    sleep(.1)
    ledY.off()
    
