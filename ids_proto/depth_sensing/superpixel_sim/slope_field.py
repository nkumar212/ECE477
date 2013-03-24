#!/usr/bin/env python

import sys

fin = open(sys.argv[1],'r')
fin.read(54)
data = fin.read()
fin.close()
