#!/usr/bin/env python

import sys

fin = open(sys.argv[1],'r')
fin.read(54)
data = fin.read()
fin.close()

print len(data)

pixel_data = ["".join([hex(ord(data[i+j]))[2:].zfill(2) for j in xrange(3)]) for i in xrange(len(data)/3)]
histo = {j:pixel_data.count(j) for j in set(pixel_data)}

for l in sorted(histo.keys(), key=(lambda x: histo[x])):
	print l,histo[l]
