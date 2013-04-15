#!/usr/bin/env python
from twisted.internet import protocol, reactor
from txws import WebSocketFactory

class Echo(protocol.Protocol):
    def dataReceived(self, data):
		print data

class EchoFactory(protocol.Factory):
    def buildProtocol(self, addr):
        return Echo()

reactor.listenTCP(9999, WebSocketFactory(EchoFactory()))
reactor.run()
