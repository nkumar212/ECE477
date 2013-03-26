CPPFLAGS = --debug -lpthread
OBJS = keepalive.o

target : ../commands.a

../commands.a : $(OBJS)
	ar crf $@ $^

depends : *.cpp
	@g++ -M $(CPPFLAGS) $^ > depends

clean :
	@rm -f *.o *.a depends

%.o : depends

-include depends
