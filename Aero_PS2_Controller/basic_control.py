'''
basic_control.py
@author: Garrett Owen
@date: January 26, 2012
    
    python verson 2.7.1

Based off code from 
http://iamtherockstar.com/archive/making-hid-devices-easier-using-pygame-joysticks/
'''

import serial
import pygame
import time
import struct

#serialPort = '/dev/tty.usbserial-A7004Jg4' # Arduino Mega
serialPort = '/dev/tty.usbmodemfd1221'       # Arduino Uno
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
        
        ''' 
            Number for each command
            #define XAXIS '0'
            #define YAXIS '1'
            #define ZAXIS '2'
            #define THROTTLE '3'
            #define MODE '4'
            #define AUX '5'
        '''
        
        diff = 0.005
        if j.get_axis(0) < axis[0] - diff or j.get_axis(0) > axis[0] + diff:
            axis[0] = j.get_axis(0)
        
        if j.get_axis(2) < axis[2] - diff or j.get_axis(2) > axis[2] + diff:
            axis[2] = j.get_axis(2)
    
        if j.get_axis(3) < axis[3] - diff or j.get_axis(3) > axis[3] + diff:
            axis[3] = j.get_axis(3)
        
        
        # Get Controller Values
        zaxis = axis[0] * 150 + 1500 # Yaw   (z-axis)
        yaxis = axis[3] * -1 * 150 + 1515 # Pitch (y-axis)
        xaxis = axis[2] * 150 + 1500 # Roll  (x-axis)
        
        # If values are close to neutral set them to 1500
        if zaxis < 1523 and zaxis > 1490:
            zaxis = 1500  
        if yaxis < 1495 and yaxis > 1520:
            yaxis = 1515  # temporary fix for rate mode
        if xaxis < 1518 and xaxis > 1481:
            xaxis = 1500  
        
        # throttle += j.get_axis(1) * -1 * 25 # Throttle
        if j.get_button(4) == 1:
            throttle -= 40
        elif j.get_button(5) == 1:
            throttle += 40
        if j.get_button(6) == 1:
            throttle -= 20
        elif j.get_button(7) == 1:
            throttle += 20
                
        if throttle > 1700:
            throttle = 1700
        elif throttle < 1000:
            throttle = 1000
                
        # Calibrate Sensors
        if j.get_button(8) == 1:
            throttle = 1000
            zaxis = 1000
            yaxis = 1000
            xaxis = 2000

        # Arm Motors
        if j.get_button(9) == 1:
            throttle = 1000
            zaxis = 2000

        # Disarm Motors
        if j.get_button(3) == 1:
            throttle = 1000
            zaxis = 1000
                
        if j.get_button(0) == 1:
            mode = 1000
        elif j.get_button(1) == 1:
            mode = 2000
        
        if j.get_button(2) == 1:
            throttle = 1000
    
        # Put Values into a command string and convert ints to bytes
        command =   "c" + \
                    ";0;" + str(int(round(xaxis))) + \
                    ";1;" + str(int(round(yaxis))) + \
                    ";2;" + str(int(round(zaxis))) + \
                    ";3;" + str(int(round(throttle))) + \
                    ";4;" + str(int(round(mode))) + \
                    ";5;" + str(int(round(aux)))
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


#        # Used to read input from the two joysticks       
#        for i in range(0, j.get_numaxes()):
#            if j.get_axis(i) != 0.00:
#                print 'Axis %i reads %.2f' % (i, j.get_axis(i))
#        
#        time.sleep(.5)
#        
#        for i in range(0, j.get_numbuttons()):
#            if j.get_button(i) != 0:
#                if not button_history[i]:
#                    print 'Button %i reads %i' % (i, j.get_button(i))
#                    button_history[i] = 1
#                    ser.write(str(i))
#            else:
#                button_history[i] = 0

except KeyboardInterrupt:
    j.quit()
