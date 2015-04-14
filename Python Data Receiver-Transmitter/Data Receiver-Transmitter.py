#!/usr/bin/python

import threading
import serial
import logging
import xSub

#THREADS

def xSub_Servidor():
	'''Este Thread se encarga de la comunicacion por tcp/ip para transmisión de datos'''
	print(threading.currentThread().getName())
	return

def xSub_Serial():
	"""Este Thread se encarga de la comunicacion por Serial para transmisión de datos"""
	print(threading.currentThread().getName())
	return

def xSub_DataLogger():
	"""Este Thread se encarga de la creación de un archivo .txt con la data recibida"""
	print(threading.currentThread().getName())
	return

#Creación de threads para multiproceso
xSub.info() #Info del Proyecto

#Log del programa
logging.basicConfig(filename='Logger/logger.txt',level=logging.DEBUG)
logging.info('Test2') # will not print anything

#Creación de Threads
Servidor = threading.Thread(name='tServidor', target = xSub_Servidor)
Serial = threading.Thread(name='tSerial', target = xSub_Serial)
DataLogger = threading.Thread(name='tDataLogger', target = xSub_DataLogger)

#Inicialización de los Threads
Servidor.start()
Serial.start()
DataLogger.start()




