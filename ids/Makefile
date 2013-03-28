CPPFLAGS = --debug -lpthread
A = commands.a
OBJ = ids.o Command.o CommandQueue.o
LIBS = -lpthread -lrt
subdirs = commands

target : ids

ids : main.cpp $(OBJ) $(A)
	g++ main.cpp $(OBJ) $(LIBS) $(A) -o ids

$(A) : $(subdirs)

depends : *.cpp
	@g++ -M $(CPPFLAGS) $^ > depends

clean :
	@rm -f *.o *.a depends

$(subdirs) : .PHONY
	-cd $@ ; $(MAKE)

.PHONY : 

%.o : depends

-include depends
