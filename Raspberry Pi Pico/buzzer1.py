from machine import Pin
import time

led=Pin(2,Pin.OUT)
buz=Pin(6,Pin.OUT)
butt=Pin(5,Pin.IN,Pin.PULL_DOWN)

while True:
    if(butt.value()==0):
        led.value(1)
        buz.value(1)
        time.sleep(2)
    else:
        led.value(0)
        buz.value(0)
        time.sleep(0.1)