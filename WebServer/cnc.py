#!/usr/bin/env python
from twisted.internet import protocol, reactor
from txws import WebSocketFactory

import json
from copy import deepcopy

class WebsocketProtocol(protocol.Protocol):
	def __init__(self):
		self.last_data = None
		self.last_keys = None

	def dataReceived(self, jdata):
		diagScale = 0

		motors = [0,0]

		#print jdata
		try:
			data = json.loads(jdata.strip())
		except:
			return

		robot = Minotaur.instances[data['robotid']]

		if data['gKeys'] == 1: #W
			motors = [1,1]
		elif data['gKeys'] == 2: #A
			motors = [-1,1]
		elif data['gKeys'] == 4: #S
			motors = [-1,-1]
		elif data['gKeys'] == 8: #D
			motors = [1,-1]
		elif data['gKeys'] == 3: #W, A
			motors = [diagScale,1]
		elif data['gKeys'] == 9: #W, D
			motors = [1,diagScale]
		elif data['gKeys'] == 6: #S, A
			motors = [-diagScale,-1]
		elif data['gKeys'] == 12: #S, D
			motors = [-1, -diagScale]

		if data['gKeys'] & 16:
			motors = [0,0]

		if data['gKeys'] == 32 and (self.last_keys & 32 == 0):
			robot.write(bytes("".join([chr(0x10),chr(0x00),chr(0x00)])))
			self.last_keys = data['gKeys']
			return

		speed = 'speed' in data.keys() and data['speed'] and int(data['speed']) or 50;
		motors = [int(m * max(min(speed * 127.0/100,127),0)) for m in motors]
		dirs = [(0,128)[m<0] for m in motors]

		codes = [1,0,0]
		codes[1] = abs(motors[0]) | dirs[0]
		codes[2] = abs(motors[1]) | dirs[1]

		if self.last_data != codes and data['robotid'] in Minotaur.instances.keys():
			char_array = [chr(c) for c in codes]
			data_str = "".join(char_array)
			robot.write(bytes(data_str))

		self.last_data = deepcopy(codes)
		self.last_keys = data['gKeys']

class Minotaur:
	instances = {}

	def __init__(self, socket):
		self.name = None
		self.loggedin = False
		self.socket = socket


	def login(self,name):
		self.name = name
		self.loggedin = True
		Minotaur.instances[name] = self

	def write(self, data):
		self.socket.transport.write(data)

class MinotaurProtocol(protocol.Protocol):
	def __init__(self):
		self.buffer = None
		self.client = None

	def connectionMade(self):
		self.minotaur = Minotaur(self)

	def dataReceived(self, data):
		if(not self.minotaur.loggedin):
			self.minotaur.login(data)
			print "Minotaur Connected with id:", self.minotaur.name,"at",self.transport.getHandle().getpeername()

minotaur_factory = protocol.ServerFactory()
minotaur_factory.protocol = MinotaurProtocol
websocket_factory = protocol.ServerFactory()
websocket_factory.protocol = WebsocketProtocol

reactor.listenTCP(9999, WebSocketFactory(websocket_factory))
reactor.listenTCP(50000, minotaur_factory)
reactor.run()
