ROOT=$(shell pwd)
SED=$(shell which sed)
MV=$(shell which mv)
RM=$(shell which rm)

define make-depend
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M $1 | \
		$(SED) 's,\($$(notdir $2)\) *:,$$(dir $2) $3: ,' > $3.tmp
	@$(MV) $3.tmp $3
endef

OBJS = keepalive.o freenect_sync.o swapdepth.o planedist.o distframe.o dumpvideo.o slopeframe.o wallframe.o posframe.o
CLEAN_TARGETS=*.o *.d *.a
subdirs = 

target : ../commands.a

../commands.a : $(OBJS)

clean:
	rm -f $(CLEAN_TARGETS)

%.a:
	ar crf $@ $^

%.o: %.cpp
	$(call make-depend,$<,$@,$(subst .o,.d,$@))
	$(COMPILE.cpp) -o $@ $<

.PHONY : $(subdirs)
