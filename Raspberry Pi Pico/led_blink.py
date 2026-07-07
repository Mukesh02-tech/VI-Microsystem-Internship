from machine import Pin
import time
led0=Pin(1,Pin.OUT)
led1=Pin(2,Pin.OUT)
led2=Pin(3,Pin.OUT)
while 1:
    led0.value(1)
    led1.value(0)
    led2.value(0)
    time.sleep(1)
    led0.value(0)
    led1.value(1)
    led2.value(0)
    time.sleep(1)
    led0.value(0)
    led1.value(0)
    led2.value(1)
    time.sleep(1)