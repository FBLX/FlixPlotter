import serial
import sys
import time
import random
import numpy as np

ser = serial.Serial('/dev/ttyACM0', 9600, timeout = 5)

baseLength = 800
height = 1000
stepsPerRev = 200
pi = np.pi
axDiam = 14

ds = pi*axDiam/stepsPerRev


def close():
    ser.close()
    sys.exit()

def calcLength(x,y):
    l = int((np.sqrt((height-y)**2+x**2)+0.5)/ds+0.5)
    r = int((np.sqrt((height-y)**2+(baseLength-x)**2)+0.5)/ds+0.5)
    return (l, r)



def send_s(_l, _r):
    text = 's -l ' + str(_l) + ' -r ' + str(r)
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

    send_r()

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
        send_d(l,r)
    if txt == 's':
        l = int(float(input("length left: "))/ds+0.5)
        r = int(float(input("length right: "))/ds+0.5)
        send_s(l,r)
    if txt == 'r':
        print('drawing...')
        send_r()
    if txt == 'i':
        send_i()

    if txt == 'h':
        haus()

    time.sleep(0.5)
    while ser.in_waiting:
        print(ser.readline())
