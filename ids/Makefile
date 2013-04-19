ROOT=$(shell pwd)
SED=$(shell which sed)
MV=$(shell which mv)
RM=$(shell which rm)

LIBS = -lpthread -lrt
CPPFLAGS = -O3 -I $(ROOT)/libfreenect/include -L $(ROOT)/libfreenect/build/lib -L $(ROOT)/libfreenect/build-alaric/lib
CLEAN_TARGETS=*.o *.d *.a

A = commands.a
OBJ = ids.o Command.o CommandQueue.o kinect.o yuv.o wall.o point.o
subdirs = commands

export ROOT
export CPPFLAGS

define make-depend
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M $1 | \
		$(SED) 's,\($$(notdir $2)\) *:,$$(dir $2) $3: ,' > $3.tmp
	@$(MV) $3.tmp $3
endef

target : ids

ids : main.o
	mv main.o ids

main.o : main.cpp $(A) $(OBJ) main_command_queue.h main_cnc_wait.h main_minos_wait.h
	g++ main.cpp $(OBJ) $(A) $(LIBS)  $(CPPFLAGS) -lfreenect -o main.o

commands.a : commands
	$(MAKE) -C commands

clean:
	rm -f $(CLEAN_TARGETS)
	$(MAKE) -C commands clean

%.a:
	ar crf $@ $^

%.o: %.cpp
	$(call make-depend,$<,$@,$(subst .o,.d,$@))
	$(COMPILE.cpp) -o $@ $<

.PHONY : $(subdirs)
