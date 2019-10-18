# -*- coding: utf-8 -*-
"""
Created on Fri Oct 18 14:41:19 2019

@author: Taavi Kase
"""
import threading
import tkinter
import serial

#This method should run on background thread
def bgThread(ser):
    print("Separate thread")
    i = 0
    while i < 10:
        line = ser.readline().decode("utf-8")
        line = line.replace("/n/r", "")
        value = int(line)
        print(value)
        i = i + 1
        print(i)

# Main method
if __name__ == "__main__":
    print("In Main")
    ser = serial.Serial("COM8")
    x = threading.Thread(target=bgThread, args=(ser,))
    x.start()
    
    #thread.join(poram) - main thread waits for background thread to finish.
    #param-timeot in seconds: if thread not finished before timeout, kill thread
    #x.join(timeout=10)
    
    top = tkinter.Tk()
    top.mainloop()
    print("after thread")
