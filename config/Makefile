BASEDIR  = .
SRCDIR	 = $(BASEDIR)/src
BUILDDIR = $(BASEDIR)/bin
LOGDIR	 = $(BASEDIR)/log

SRCS = 
OBJS = 

include $(BASEDIR)/config/Makefile.config
include $(BASEDIR)/config/Makefile.rules

.PHONY: clean

machina: $(SRCS)	
	$(CPP) $(CCFLAGS) $(CPPFLAGS) $(PREPROC) $(INCL) $(SRCS) -o $(BUILDDIR)/$@ 
	
clean:
	rm $(BUILDDIR)/machina
test:
	./$(BUILDDIR)/machina



