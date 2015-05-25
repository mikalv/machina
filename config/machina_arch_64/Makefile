BASEDIR  = .
SRCDIR	 = $(BASEDIR)/src
BUILDDIR = $(BASEDIR)/bin
LOGDIR	 = $(BASEDIR)/log

SRCS = 
OBJS = 

include $(BASEDIR)/config/machina_arch_64/Makefile.config
include $(BASEDIR)/config/machina_arch_64/Makefile.rules

.PHONY: clean

machina-64: $(SRCS)	
	$(CPP) $(CCFLAGS) $(CPPFLAGS) $(PREPROC) $(SRCS) -o $(BUILDDIR)/$@ 
	
clean:
	rm $(BUILDDIR)/machina-64
test:
	./$(BUILDDIR)/machina-64



