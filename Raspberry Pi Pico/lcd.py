from machine import Pin
from gpio_lcd import GpioLcd
import time
# Initialize the LCD
lcd = GpioLcd(rs_pin=Pin(8),
              enable_pin=Pin(9),
              d4_pin=Pin(10),
              d5_pin=Pin(11),
              d6_pin=Pin(12),
              d7_pin=Pin(13),
              num_lines=2,         # Important: define 2 lines
              num_columns=16)      # Important: define 16 columns

# Display first line
lcd.move_to(0, 0)
lcd.putstr("Welcome to")

# Display second line
lcd.move_to(0, 1)
lcd.putstr("VI Microsystems")

# Optional: keep text for some time
while True:
    pass
