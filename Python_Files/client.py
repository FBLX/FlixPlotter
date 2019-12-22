import serial
import sys
import time
import random
import numpy as np

import matplotlib.pyplot as plt

ser = serial.Serial('/dev/ttyACM1', 9600, timeout = 5)

baseLength = 800 # distance between rotors
height = 1000 # canvas height
stepsPerRev = 200 # steps per revolution
pi = np.pi # PI
axDiam = 14 # axis diameter of stepper motors

ds = pi*axDiam/stepsPerRev # step size 

res = 8 # drawing resolution in mm 


def close():
    ser.close()
    sys.exit()

def calcLength(x,y):
    l = int((np.sqrt((height-y)**2+x**2)+0.5)/ds+0.5)
    r = int((np.sqrt((height-y)**2+(baseLength-x)**2)+0.5)/ds+0.5)
    return (l, r)



def send_s(_l, _r, _s):
    text = 's -l ' + str(_l) + ' -r ' + str(r) + ' -s ' + str(_s)
    text = text.encode()
    ser.write(text)
    ser.write(b'\n')
def send_d():
    l = str(random.randint(1,400))
    r = str(random.randint(1,400))
    l = l.encode()
    r = r.encode()
    text = b'd -l 500 -r 400'
    ser.write(text)
    ser.write(b'\n')
def send_m(_l, _r):
    text = 'm -l ' + str(_l) + ' -r ' + str(_r)
    text = text.encode()
    #text = b'm -l '+l+' -r '+r
    ser.write(text)
    ser.write(b'\n')
def send_r():
    text = b'r'
    ser.write(text)
    ser.write(b'\n')
def send_i():
    text = b'i'
    ser.write(text)

def haus():
    x = [200, 200, 400, 600, 600, 200]
    y = [300, 600, 800, 600, 300, 300]

    for i,j in zip(x,y):
        l,r = calcLength(i,j)
        send_m(l,r)


def line(start, end):
    distance = np.sqrt((abs(end[0]-start[0]))**2+(abs(end[1]-start[1]))**2)
    points = distance / res
    print (points)
    x = np.linspace(start[0], end[0], points)
    y = np.linspace(start[1], end[1], points)


    for i,j in zip(x,y):
        l,r = calcLength(i,j)
        send_m(l,r)
        time.sleep(0.01)


def circle(center, r):
    diam = 2*pi*r
    points = diam / res
    dp = np.linspace(0,2*pi, points)
    x = np.copy(dp)
    y = np.copy(dp)
    x = center[0] + r*np.cos(x)
    y = center[1] + r*np.sin(y)

    
    plt.plot(x,y)

    for i,j in zip(x,y):
        l,r = calcLength(i,j)
        send_m(l,r)
        time.sleep(0.01)




while(1):
    txt = input("$ ")
    print(txt)
    if txt == 'c':
        close()

    if txt == 'm':
        x = float(input("x: "))
        y = float(input("y: "))
        l,r = calcLength(x,y)
        send_m(l,r)
    if txt == 'd':
        send_d(l,r,s)
    if txt == 's':
        l = int(float(input("length left: "))/ds+0.5)
        r = int(float(input("length right: "))/ds+0.5)
        s = int(input("max speed: "))
        send_s(l,r,s)
    if txt == 'r':
        print('drawing...')
        send_r()
    if txt == 'i':
        send_i()

    if txt == 'n':
        haus()

    if txt == 'l':
        s = (300,400)
        e = (600,600)
        line(s,e)

    if txt == 'k':
        cc = (300,400)
        rr = 100
        circle(cc,rr)

    time.sleep(0.5)
    while ser.in_waiting:
        print(ser.readline())
