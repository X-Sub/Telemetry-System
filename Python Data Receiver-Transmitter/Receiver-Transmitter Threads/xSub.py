
import threading
import serial
import logging
import time
import datetime
from pynmea import nmea


PuertoS_xSub = 'COM7'
PuertoS_GPS = 'COM3' #GPS

def info():
	infoProyecto = u"El X-Sub es un proyecto del Grupo de Investigacion y Desarrollo en Mecatronica"
	print(infoProyecto)

version = '0.1'


def logInit(ruta):
	logging.basicConfig(filename='C:/dataLog_test/datalog.txt',level=logging.DEBUG)
	Head = datetime.datetime.now().strftime(" Fecha: %d/%m/%Y Hora: %H:%M:%S")
	logging.info(Head)




##THREADS
class Threads():

	statusOK = False

	def startThreads(self):
		#Inicialización de los Threads
		statusOK = True
		self.Servidor.start()
		self.Serial.start()
		self.DataLogger.start()
		



	def xSub_Servidor():
		'''Este Thread se encarga de la comunicacion por tcp/ip para transmisión de datos'''
		print("threading.currentThread().getName()")
		while True:
			print("HOLA")
		




	def xSub_Serial():
		"""Este Thread se encarga de la comunicacion por Serial para transmisión de datos"""
		#print(threading.currentThread().getName())
		#ser1 = serial.Serial('COM7',115200)
		##x = ser.read()          # read one byte
		#s = ser.read(3)        # read up to ten bytes (timeout)
		#print(s)
	#
		#ser.close()
		try:
			ser = serial.Serial(xSub.PuertoS_GPS,57600)
			while True:
				# read what is on serial port
				data = ser.readline().decode("ASCII")
				#data = '$GPGGA,180914.600,1024.6583,N,06652.9368,W,2,6,1.09,1201.0,M,-18.1,M,0000,0000*5B\r\n'
				#print(data)
				#reads bytes followed by a newline
				if data[0:6] == '$GPGGA':
					#print(data)      #print the sentence to the console
					gpgga = nmea.GPGGA()  # class constructor
					gpgga.parse(data)   # method for parsing the sentence
					lats = gpgga.latitude
					lat_dir = gpgga.lat_direction
					longs = gpgga.longitude
					long_dir = gpgga.lon_direction
					time = gpgga.timestamp
					alt = gpgga.antenna_altitude
					print(time + '\n')
					Hora = 'Hora UTC:' + time[0:2] + ':' + time[2:4] + ':' + time[4:6]
					print(Hora)
					logging.info(Hora)
					time.sleep(1) 
		except:
			print("Problema de Puerto Serial")
			

	def xSub_DataLogger():
		"""Este Thread se encarga de la creación de un archivo .txt con la data recibida"""
		print("xSub_Datalogger")
		return



	#Creación de Threads
	Servidor = threading.Thread(name='tServidor', target = xSub_Servidor)
	Serial = threading.Thread(name='tSerial', target = xSub_Serial)
	DataLogger = threading.Thread(name='tDataLogger', target = xSub_DataLogger)






















