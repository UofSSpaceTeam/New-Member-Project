#!/usr/bin/env python3
import serial
from datetime import datetime

def parse(line):
	inside1 = float(line[0])
	inside2 = float(line[1])
	inside3 = float(line[2])
	inside4 = float(line[3])

	outside1 = float(line[4])
	outside2 = float(line[5])
	outside3 = float(line[6])
	outside4 = float(line[7])

	insideAverage = float(line[8])
	outsideAverage = float(line[9])
	difference = float(line[10])
	concerning = int(line[11])

	timeStamp = datetime.now()


	log = str(timeStamp) + "," + str(inside1) + "," + str(inside2) + "," + str(inside3) + "," + str(inside4) + "," + str(outside1) + "," + str(outside2) + "," + str(outside3) + "," + str(outside4) + "," + str(insideAverage) + "," + str(outsideAverage) + "," + str(difference) + "," + str(concerning) + "\n"
	file = open("logFile.csv", "a")
	file.write(log)
	file.close()


ser = serial.Serial("/dev/ttyACM0", 9600)


while True:
	ready = False
	read_serial = ser.readline()
	try:
		decoded_serial = read_serial.decode('utf-8')
	except Exception as e:
		file = open("logFile.csv", "a")
		print(e)
		file.write(str(datetime.now()) + ", EXCEPTION OCCURRED: "+str(e) + "\n")
		file.close()
		continue
	serialHex = str(decoded_serial)
	line = serialHex.rstrip()
	newLine = line.rsplit(",")
	ready = (len(newLine)==12)
	if ready:
		parse(newLine)
	print(newLine)





