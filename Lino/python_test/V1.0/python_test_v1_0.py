import time
import serial
from tkinter import *
from tkinter.colorchooser import *

print("Serial color sender. V1.0 - Enrico Sanino\n")

error = 0
passed = 0


while (passed == 0 or error == 1):
        ser = serial.Serial()
        print('Open <port> <speed>: ')

        if (ser.isOpen() == True):
                ser.close()
        
        input_str = input()
        i = 0
        while input_str[i] != ' ':
                i=i+1
        _port = input_str[0:i]
        i=i+1
        speed = int(input_str[i:])

        print ("Connecting to host... port = "+str(_port)+" speed = " + str(speed))
        if (ser.isOpen() == True):
                ser.close()
        ser = serial.Serial(port = _port, baudrate = speed, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1, xonxoff=False, rtscts=False, writeTimeout=None, dsrdtr=False, interCharTimeout=None)
        #print("Usage: XX in hex (MSB->LSB), separated with <space>. Send using ENTER. \n")
        ctrl = 1
        while ctrl != 0:
                input_str = askcolor()
                red = input_str[1][1:3]
                green = input_str[1][3:5]
                blue = input_str[1][5:7]
                #if (red[0] != '0' and  red[1] != '0' and  green[0] != '0' and  green[1] != '0' and  blue[0] != '0' and  blue[1] != '0'):
                 #       intRed = int(red[0])+int(red[1]
                  #      white = '00'        
                white = '00'
                
                #input_str = input("> ")
                print(input_str[1])
                ser.write('$'.encode())
                #block ifc
                ser.write('0'.encode())
                ser.write('0'.encode())
                #
                ser.write(red[0].encode())
                ser.write(red[1].encode())
                ser.write(green[0].encode())
                ser.write(green[1].encode())
                ser.write(blue[0].encode())
                ser.write(blue[1].encode())
                ser.write(white[0].encode())
                ser.write(white[1].encode())
                #light int
                ser.write('6'.encode())
                ser.write('4'.encode())
                #res
                ser.write('3'.encode())
                ser.write('f'.encode())
                #res
                ser.write('8'.encode())
                ser.write('0'.encode())

                ser.write('#'.encode())
print("end")
