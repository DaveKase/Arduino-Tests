# -*- coding: utf-8 -*-
"""
Created on Fri Oct 18 14:41:19 2019

@author: Taavi Kase
"""
# Imports (importing only libraries from vpython, that we're going to use)
import serial
from vpython import vector
from vpython import color
from vpython import box
from vpython import radians

# Main method
if __name__ == "__main__":
    # Storing previous angle
    oldAngle = 0.0
    # Opening serial port. Port was created by Arduino IDE
    ser = serial.Serial("COM8")
    
    # Creating bigger, red box
    background = box(pos = vector(0, 0, 0), axis = vector(0.5, 1, 1), 
                     length = 20, hight = 1, width = 1, color = color.red)
    
    # Creating smaller, cyan box, that seems like it is connected to the bigger box
    block = box(pos = vector(0, 0, 0), axis = vector(1, 1, 1), length = 10, 
                hight = 1, width = 1, color = color.cyan, opasity = 0)
    
    # Flag used to indicate if while loop should run.
    shouldRun = True
   
    while shouldRun:
        # Reading a line from Serial port
        data = ser.readline().decode("utf-8")
        
        # Replacing line end characters with empty string
        data = data.replace("\r\n", "")
        
        # Printing out received and edited data
        print("data = " + data)
        
        """
        If data received contains "END", ending while loop by setting shouldRun
        flag to false. If this is true, the while loop starts again from beginning
        and since shouldRun flag is false wich means while loop condition is 
        false and loop stops executing
        """
        if data == "END":
            shouldRun = False
        else:
            # If we have data (checking if didn't work properly here), typecast it to float
            # calculate angle from it and rotate smaller block with radian of the angle
            position = int(data)
            angle = position * 360.0 / 255.0
            print("angle %s" %angle)
            
            # rotate() rotates block with reference of the previous angle
            # If we take oldAngle off of the angle, we get the rotation that corresponds
            # to the rotation of the encoder
            block.rotate(radians(angle - oldAngle))
            oldAngle = angle
    
    # Printing out that program ends
    print("Program Ending")
