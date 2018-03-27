#!/usr/bin/python
import sys
PATH = "/sys/class/leds/beaglebone:green:usr"

def writeLED(fn, value, led):
	fo = open(PATH + led + fn, "w")
	fo.write(value)
	fo.close()
	return

def removeTrigger(led):
	writeLED("/trigger", "none", led)
	return
	
def command(cmd, led):
	if(cmd == 1):
		print "Turning usr%s ON" %led
		writeLED("/brightness", "1", led)
	elif(cmd == 2):
		print "Turning usr%s OFF" %led
		writeLED("/brightness", "0", led)
	elif(cmd == 3):
		print "Flashing usr%s" %led
		writeLED("/trigger", "timer", led)
		writeLED("/delay_on", "500", led)
		writeLED("/delay_off", "500", led)
	elif(cmd == 4):
		fo = open(PATH + led + "/trigger", "r")
		print fo.read()
		fo.close()
	else:
		print "\nInvalid command %s" %str(cmd)
	return
	
def main():
	print "\n===================================="
	print "Starting the LED Program"
	print "USER LED: usr0 [1], usr1 [2], usr2  [4], usr3   [8]"
	print "Commands: ON   [1], OFF  [2], FLASH [3], STATUS [4]"
	print "Exit: 0"
	print "===================================="
	bw = int(input("Enter USER LED >> "))
	
        while(bw != 0):
            cmd = input("Enter command >> ")
            print "\n"
		
            if((bw & 1) == 1): command(cmd, "0")
            if((bw & 2) == 2): command(cmd, "1")
            if((bw & 4) == 4): command(cmd, "2")
            if((bw & 8) == 8): command(cmd, "3")
            bw= input("\nEnter USER LED >> ");
    	
        print "\n"
        for i in range(0,4):
            removeTrigger(str(i))
            command(2, str(i))

main()
print "\nEnd of LED Program\n"
