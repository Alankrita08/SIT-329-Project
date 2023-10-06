import serial
import os
import RPi.GPIO as GPIO
import urllib.request
import time

os.system("cd /home/pi/.local/bin")
from RPLCD import i2c

def SerialCommRead():
    global ser
    if ser.in_waiting>0:
        Val=ser.readline().decode("ascii").rstrip()
        return Val

# constants to initialise the LCD
lcdmode = 'i2c'
cols = 16
rows = 2
charmap = 'A00'
i2c_expander = 'PCF8574'

# Generally 27 is the address;Find yours using: i2cdetect -y 1 
address = 0x27 
port = 1 # 0 on an older Raspberry Pi

# Initialise the LCD
lcd = i2c.CharLCD(i2c_expander, address, port=port, charmap=charmap,
                  cols=cols, rows=rows)

ser=serial.Serial('/dev/ttyACM0',9600)
ser.flush()


GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

Mes='Weather System'
lcd.cursor_pos = (0, 0)
lcd.write_string(Mes)
lcd.crlf()
while True:
    Val=SerialCommRead()
    ser.flush()
    if str(Val)!='None':
        print(Val)
        LocT=Val.find("T")
        LocR=Val.find("R")
        LocM=Val.find("M")
        lcd.crlf()
        lcd.write_string("                ")
        lcd.crlf()
        lcd.write_string(Mes)
        lcd.crlf()
        lcd.write_string("T:"+str(Val[2:LocR-1])+' R:'+str(Val[LocR+2:LocM-1])+' G:'+str(Val[LocM+2:]))
        lcd.crlf()
        Link="https://api.thingspeak.com/update?api_key=N9MAI1JZJOJMGI0X&field1="+str(Val[2:LocR-1])+"&field2="+str(Val[LocR+2:LocM-1])+"&field3="+str(Val[LocM+2:])
        Rspn=urllib.request.urlopen(Link)
        time.sleep(10)
        
