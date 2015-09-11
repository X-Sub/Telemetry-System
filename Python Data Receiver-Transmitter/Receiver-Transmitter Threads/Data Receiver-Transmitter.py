#!/usr/bin/python
'''Politicas'''

import threading
import serial
import logging
import xSub
import time
import datetime
from pynmea import nmea
from xSub	import Threads



#Creación de threads para multiproceso
xSub.info() #Info del Proyecto
tXSub = Threads()
tXSub.startThreads()





