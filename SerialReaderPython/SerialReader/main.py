# -*- coding: utf-8 -*-
"""
Created on Fri Oct 18 14:41:19 2019

@author: Taavi Kase
"""
import threading
import serial
from vpython import *

def bgThread(ser):
    print("Separate thread")
    counter = 0;
   
    while counter < 15:
        print("in while, counter = %s" %counter)
        line = ser.readline().decode("utf-8")
        line = line.replace("/n/r", "")
        value = int(line)
        counter += 1
        print(value)

# Main method
if __name__ == "__main__":
    print("Main called")
    sphere()
    #box()
    ser = serial.Serial("COM8")
    x = threading.Thread(target=bgThread, args=(ser,))
    x.start()


"""
import threading
import tkinter
import serial

global captureSerial
global canvas
#This method should run on background thread
def bgThread(ser):
    global captureSerial
    global canvas
    print("Separate thread, capture = ", captureSerial)
   
    while captureSerial == True:
        print("in while")
        line = ser.readline().decode("utf-8")
        line = line.replace("/n/r", "")
        value = int(line)
        
        canvas = tkinter.Canvas(top, bg="blue", height=value, width=value)
        #canvas.pack()
        #top.mainloop()
        print(value)

def startButton():
    global captureSerial
    global canvas
    captureSerial = True
    print("START ")
    ser = serial.Serial("COM8")
    x = threading.Thread(target=bgThread, args=(ser,))
    canvas = tkinter.Canvas(top, bg="blue", height=100, width=10)
    x.start()

def stopButton():
    global captureSerial
    captureSerial = False
    print("STOP")

# Main method
if __name__ == "__main__":
    print("In Main")
    global captureSerial
    global canvas
    captureSerial = False
    
    top = tkinter.Tk()
    start = tkinter.Button(top, text = "Start", command = startButton)
    stop = tkinter.Button(top, text = "Stop", command = stopButton)
    canvas = tkinter.Canvas(top, bg="blue", height=10, width=10)
    
    start.pack()
    stop.pack()
    canvas.pack()
    top.mainloop()
    print("after thread")
    
"""