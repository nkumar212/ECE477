#!/usr/bin/env python

import sys
import math

AVG_SIZE=int(sys.argv[3])
fout = sys.stdout

hin = open(sys.argv[1],'r')
fout.write(hin.read())

fin = open(sys.argv[2],'r')
data = fin.read()
avgy_data = []
slope_data = []

for row in xrange(0,480):
	for col in xrange(0,640,AVG_SIZE):
		avg = [ord(data[(row * 640 + col + a)*2]) for a in xrange(0,AVG_SIZE)]
		avgy_data.append(sum(avg)/len(avg))

	#sys.stderr.write("%d\n"%(sum(avg)/len(avg)))

p = 0

for row in xrange(479,-1,-1):
	for col in xrange(639,-1,-1):
		p += 1
		points = [avgy_data[(row - row % AVG_SIZE + a) * (640/AVG_SIZE) + col/AVG_SIZE] for a in xrange(0,AVG_SIZE)]
		slopes = [points[a] - points[a-1] for a in xrange(1,AVG_SIZE)]

		avg_slope = sum(slopes)/len(slopes)
		var_slope = math.sqrt(sum([(s-avg_slope)**2 for s in slopes]))

		out_avg = chr(max(min(int(avg_slope)*30+128,255),0))
		out_var = chr(max(min(int(var_slope)*5+128,255),0))
#		for i in xrange(AVG_SIZE):
		fout.write(out_avg)
		fout.write(out_var)
		fout.write('\x00')

sys.stderr.write("%d %d %d %d\n" % ( len(data)/2, p,len(avgy_data),len(avgy_data)/AVG_SIZE))
