CPPFLAGS = --debug -lpthread
A = commands.a
OBJ = ids.o Command.o CommandQueue.o
subdirs = commands

target : ids

ids : main.cpp $(OBJ) $(LIBS) $(A)
	g++ main.cpp $(OBJ) $(LIBS) $(A) -o ids

$(A) : subdirs

depends : *.cpp
	@g++ -M $(CPPFLAGS) $^ > depends

clean :
	@rm -f *.o *.a depends

%.o : depends

-include depends
