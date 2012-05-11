'''
basic_control.py
@author: Garrett Owen
@date: April 27, 2012
    
for python verson 2.7.1
'''

import serial
import pygame
import time
import struct

serialPort = '/dev/tty.usbmodemfa131'       # Arduino Uno
baudRate = 38400

# Open Serial Connection to Arduino Board
ser = serial.Serial(serialPort, baudRate, timeout=1);


'''
Gets joystick data and prints it
'''
pygame.init()
#joystick.init()
j = pygame.joystick.Joystick(0)
j.init()
print 'Initialized Joystick : %s' % j.get_name()

# Keeps a history of buttons pressed so that one press does
# not send multiple presses to the Arduino Board
axis = [0.0,0.0,0.0,0.0]
throttle = 1000
mode = 1000 # rate mode is < 1500, else it is attitude
aux = 1000

try:
    while True:
        pygame.event.pump()
                
        axis[0] = j.get_axis(0)
        axis[2] = j.get_axis(2)
        axis[3] = j.get_axis(3)        
        
        # Get Controller Values
        zaxis = axis[0] * 150 + 1500 # Yaw   (z-axis)
        yaxis = axis[3] * -1 * 150 + 1515 # Pitch (y-axis)
        xaxis = axis[2] * 150 + 1500 # Roll  (x-axis)
        
        # If values are close to neutral set them to 1500
        if zaxis < 1523 and zaxis > 1490:
            zaxis = 1500  
        if yaxis < 1523 and yaxis > 1490:
            yaxis = 1500  # trim for copter, otherwise it tends backwards
        if xaxis < 1518 and xaxis > 1481:
            xaxis = 1500  
        
        yaxis = yaxis + 20
        
        # Get throttle position
        throttle += j.get_axis(1) * -1 # Throttle
        if j.get_button(4) == 1:
            throttle -= 20
        elif j.get_button(5) == 1:
            throttle += 20
        if j.get_button(6) == 1:
            throttle -= 10
        elif j.get_button(7) == 1:
            throttle += 10
                
        # Max throttle set to 1650
        if throttle > 1550:
            throttle = 1570
        elif throttle < 1000:
            throttle = 1000
                
        # Calibrate Sensors - button labelled 9
        if j.get_button(8) == 1:
            throttle = 1000
            zaxis = 1000
            yaxis = 1000
            xaxis = 2000

        # Arm Motors - button labelled 10
        if j.get_button(9) == 1:
            throttle = 1000
            zaxis = 2000
                
        # Change mode
        if j.get_button(0) == 1:
            mode = 1000 # rate mode - button labelled 1
        elif j.get_button(1) == 1:
            mode = 2000 # attitude mode - button labelled 2
        
        # Disarm off motors - button labelled 3
        if j.get_button(2) == 1:
            throttle = 1000
            zaxis = 1000
    
        ''' 
        Number for each command
        XAXIS '0'
        YAXIS '1'
        ZAXIS '2'
        THROTTLE '3'
        MODE '4'
        AUX '5'
        '''

        # Put Values into a command string and convert ints to bytes
        command =   \
                    "Roll: " + str(int(round(xaxis))) + \
                    " Pitch: " + str(int(round(yaxis))) + \
                    " Yaw: " + str(int(round(zaxis))) + \
                    " Throttle: " + str(int(round(throttle))) + \
                    " Mode: " + str(int(round(mode))) + \
                    " Aux: " + str(int(round(aux)))
        print(command)
        
        # Send Commands
        ser.write('c')
        ser.write('0');
        ser.write( struct.pack('h', int(round(xaxis))) )
        ser.write('1');
        ser.write( struct.pack('h', int(round(yaxis))) )
        ser.write('2');
        ser.write( struct.pack('h', int(round(zaxis))) )
        ser.write('3');
        ser.write( struct.pack('h', int(round(throttle))) )
        ser.write('4');
        ser.write( struct.pack('h', int(round(mode))) )
        ser.write('5');
        ser.write( struct.pack('h', int(round(aux))) )
        
        
        # Only send 5 times per second
        time.sleep(.2)

except KeyboardInterrupt:
    j.quit()
