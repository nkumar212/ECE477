#!/usr/bin/env python

import sys
import math

AVG_SIZE=int(sys.argv[3])
fout = sys.stdout

hin = open(sys.argv[1],'r')
fout.write(hin.read())

fin = open(sys.argv[2],'r')
data = fin.read()
avgx_data = []
avgy_data = []

for row in xrange(0,480,AVG_SIZE):
	for col in xrange(0,640):
		avg = [ord(data[((row + a) * 640 + col)*2]) for a in xrange(0,AVG_SIZE)]
		avgx_data.append(sum(avg)/len(avg))

	#sys.stderr.write("%d\n"%(sum(avg)/len(avg)))

for row in xrange(0,480):
	for col in xrange(0,640,AVG_SIZE):
		avg = [ord(data[(row * 640 + col + a)*2]) for a in xrange(0,AVG_SIZE)]
		avgy_data.append(sum(avg)/len(avg))

p = 0

for row in xrange(479,-1,-1):
	for col in xrange(639,-1,-1):
		p += 1
		points_x = [avgx_data[(row / AVG_SIZE) * 640 + (col - col % AVG_SIZE + a)] for a in xrange(0,AVG_SIZE)]
		slopes_x = [points_x[a] - points_x[a-1] for a in xrange(1,AVG_SIZE)]

		avg_slope_x = sum(slopes_x)/len(slopes_x)
		var_slope_x = sum([(s-avg_slope_x)**2 for s in slopes_x])

		out_avg_x = chr(max(min(int(avg_slope_x)*30+128,255),0))
		out_var_x = chr(max(min(int(var_slope_x)*5+128,255),0))

		points_y = [avgy_data[(row - row % AVG_SIZE + a) * (640/AVG_SIZE) + col/AVG_SIZE] for a in xrange(0,AVG_SIZE)]
		slopes_y = [points_y[a] - points_y[a-1] for a in xrange(1,AVG_SIZE)]

		avg_slope_y = sum(slopes_y)/len(slopes_y)
		var_slope_y = sum([(s-avg_slope_y)**2 for s in slopes_y])

		out_avg_y = chr(max(min(int(avg_slope_y)*40+128,255),0))
		out_var_y = chr(max(min(int(var_slope_y)*5+128,255),0))

		out_stddev = chr(max(min(int((math.sqrt(var_slope_y+var_slope_x))*15+128),255),0))

		r,g,b = out_avg_x, out_avg_y, out_stddev
		fout.write(b)
		fout.write(g)
		fout.write(r)

sys.stderr.write("%d %d %d %d\n" % ( len(data)/2, p,len(avgy_data),len(avgy_data)/AVG_SIZE))
