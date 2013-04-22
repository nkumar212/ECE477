#!/usr/bin/env python
from twisted.internet import protocol, reactor
from txws import WebSocketFactory

import json
from copy import deepcopy
import struct

class WebsocketProtocol(protocol.Protocol):
	def __init__(self):
		self.last_data = None
		self.last_keys = None
		self.connected = 0

	def dataReceived(self, jdata):
		if not self.connected:
			print 'Client Connected at',self.transport.getHandle().getpeername()
			self.connected = 1

		diagScale = 0

		motors = [0,0]

		try:
			data = json.loads(jdata.strip())
		except:
			return

		if 'robotid' not in data.keys() or data['robotid'] not in Minotaur.instances.keys():
			if len(Minotaur.instances):
				print data['robotid'],"not a valid robot"
				print "Valid robots are:", "".join(Minotaur.instances.keys())
			return
		else:
			robot = Minotaur.instances[data['robotid']]

		if 'command' in data.keys() and data['command'] == 0x30:
			robot.requestMetrics(self)
			return

		if 'gKeys' not in data.keys() or data['gKeys'] == None:
			data['gKeys'] = 0

		try:
			data['speed'] = int(data['speed'])
			if data['speed'] > 100 or data['speed'] < 0:
				data['speed'] = 0
		except:
			data['speed'] = 0

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

		if self.last_keys != None and (data['gKeys'] & 31 !=self.last_keys & 31):
			speed = data['speed']
			motors = [int(m * max(min(speed * 127.0/100,127),0)) for m in motors]
			dirs = [(0,128)[m<0] for m in motors]

			left = abs(motors[0])|dirs[0]
			right = abs(motors[1])|dirs[1]
			robot.sendCmd( 0x01, left, right)

		if self.last_keys == 0:
			if data['gKeys'] == 32:
				robot.sendCmd(0x10, 0x00, 0x00)
			elif data['gKeys'] == 64:
				robot.sendCmd(0x20, 0x01, 0x00)
			elif data['gKeys'] == 128:
				robot.sendCmd(0x20, 0x02, 0x00)
			elif data['gKeys'] == 256:
				robot.sendCmd(0x20, 0x04, 0x00)
			elif data['gKeys'] == 512:
				robot.sendCmd(0x20, 0x07, 0x00)
			elif data['gKeys'] == 1024:
				robot.sendCmd(0x21, 0x00, 0x00)
			elif data['gKeys'] == 2048:
				robot.sendCmd(0x22, 0x00, 0x00)
			elif data['gKeys'] == 4096:
				robot.sendCmd(0x23, 0x00, 0x00)

		self.last_keys = data['gKeys']

class Minotaur:
	instances = {}

	def __init__(self, socket):
		self.name = None
		self.loggedin = False
		self.socket = socket
		self.requests = {}

	def login(self,name):
		self.name = name
		self.loggedin = True
		Minotaur.instances[name] = self

	def write(self, data):
		self.socket.transport.write(data)

	def sendCmd(self, command, data1, data2):
		print "Writing command to robot",self.name,hex(command), hex(data1), hex(data2)
		self.write(bytes("".join([chr(command % 256),chr(data1 % 256),chr(data2 % 256)])))
	
	def requestMetrics(self, client):
		if 0x30 not in self.requests.keys(): self.requests[0x30] = set()
		self.requests[0x30].add(client)
		if len(self.requests[0x30]) == 1:
			self.sendCmd(0x30, 0x00, 0x00)

class MinotaurProtocol(protocol.Protocol):
	def __init__(self):
		self.buffer = None
		self.client = None

	def connectionMade(self):
		self.minotaur = Minotaur(self)

	def dataReceived(self, data):
		if(not self.minotaur.loggedin):
			self.minotaur.login(data)
			print "Minotaur Connected with id:", self.minotaur.name,'at',self.transport.getHandle().getpeername()
		else:
			command = struct.unpack("<B",data[0])[0]
			if command == 0x30:
				if command in self.minotaur.requests.keys():
					try:
						metrics_tuple = struct.unpack("<BIfffHHBB",data)
					except struct.error:
						print "Minotaur returned invalidly formatted metric data"
						return

					metrics = (
							'command',
							'timestamp',
							'x','y',
							'orient',
							'left_encoder','right_encoder',
							'ir_bank',
							'battery'
						)
					metrics = dict(zip(metrics,metrics_tuple))
					for client in self.minotaur.requests[command]:
						client.transport.write(json.dumps(metrics))

					self.minotaur.requests[command] = set()
				

minotaur_factory = protocol.ServerFactory()
minotaur_factory.protocol = MinotaurProtocol
websocket_factory = protocol.ServerFactory()
websocket_factory.protocol = WebsocketProtocol

reactor.listenTCP(9999, WebSocketFactory(websocket_factory))
reactor.listenTCP(50000, minotaur_factory)
reactor.run()
