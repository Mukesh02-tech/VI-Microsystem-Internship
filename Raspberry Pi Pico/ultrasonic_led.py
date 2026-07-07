from machine import Pin
import utime
import time
led=Pin(3,Pin.OUT)
trigger =Pin(15,Pin.OUT)
echo=Pin(14,Pin.IN)
while True:
    trigger.low()
    utime.sleep_us(2)
    trigger.high()
    utime.sleep_us(5)
    trigger.low()
    while echo.value()==0:
        signaloff=utime.ticks_us()
    while echo.value() ==1:
        signalon=utime.ticks_us()
    timepassed=signalon-signaloff
    distance=(timepassed*0.0343)/2
    print("Total distance",distance,"cm")
    print("sensor")
    if(distance>=50):
        led.value(1)
    else:
        led.value(0)
    utime.sleep(0.5)