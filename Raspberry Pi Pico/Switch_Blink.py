from machine import Pin
import time

led1=Pin(2,Pin.OUT)
button1=Pin(4,Pin.IN,Pin.PULL_DOWN)
led2=Pin(3,Pin.OUT)
button2=Pin(5,Pin.IN,Pin.PULL_DOWN)
while True:
    if button1.value()==0:
        led1.value(1)
        print(button1.value())
    else:
        led1.value(0)
    time.sleep(0.1)
    
    if button2.value()==0:
        led2.value(1)
        print(button2.value())
    else:
        led2.value(0)
    time.sleep(0.1)