A = commands.a
OBJ = ids.o Command.o CommandQueue.o kinect.o yuv.o
LIBS = -lpthread -lrt
subdirs = commands
ROOT=$(PWD)
export ROOT
export CPPFLAGS
CPPFLAGS = --debug -I $(ROOT)/libfreenect/include -L $(ROOT)/libfreenect/build/lib

target : ids

ids : main.cpp $(A) $(OBJ) main_command_queue.h
	-echo $(CPPFLAGS)
	-echo $(OBJ)
	-echo $(LIBS)
	-echo $(A)
	g++ main.cpp $(OBJ) $(A) $(LIBS)  $(CPPFLAGS) -lfreenect -o ids

$(A) : $(subdirs)

depends : *.cpp
	@g++ -M $(CPPFLAGS) $^ > depends

clean :
	@rm -f *.o *.a depends

	$(MAKE) -C commands clean

$(subdirs) : .PHONY
	$(MAKE) -C $@

.PHONY : 

%.o : depends

-include depends
