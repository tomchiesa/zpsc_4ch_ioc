#!/usr/bin/python3

#Parsing comma separated list in text file
import numpy as np
from numpy import *
import math
from math import *
import sys
import time 
import cothread
from cothread.catools import caput, caget

timestamp=0 

while True:
	timestamp = caget('ALSU4:BTA{PSC2}LIVE_TIMESTAMP')
	print(hex(timestamp))
	time.sleep(60)        


    


    





