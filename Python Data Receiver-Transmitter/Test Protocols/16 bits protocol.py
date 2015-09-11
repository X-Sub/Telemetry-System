import serial
import time
import struct


PuertoS_xSub = 'COM3'

try:
	ser = serial.Serial(PuertoS_xSub,115200)
	while True:
		
		v = input("Introduzca la velocidad deseada (0-1023): ")
		print("velocidad enviada: " + v)
		v = int(v)
		v =  struct.pack(">H",v)
		ser.write(v)
except:
	print("Problema de Puerto Serial")
	time.sleep(1)