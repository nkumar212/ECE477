OBJS = keepalive.o freenect_sync.o swapdepth.o planedist.o distframe.o dumpdist.o slopeframe.o

target : ../commands.a

../commands.a : $(OBJS)
	ar crf $@ $^

depends : *.cpp
	@g++ -M $(CPPFLAGS) $^ > depends

clean :
	@rm -f *.o *.a depends

%.o : depends

-include depends
