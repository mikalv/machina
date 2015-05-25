BASEDIR  = .
SRCDIR	 = $(BASEDIR)/src
BUILDDIR = $(BASEDIR)/bin
LOGDIR	 = $(BASEDIR)/log

SRCS = 
OBJS = 

include $(BASEDIR)/config/machina_arch_32/Makefile.config
include $(BASEDIR)/config/machina_arch_32/Makefile.rules

.PHONY: clean

machina-32: $(SRCS)	
	$(CPP) $(CCFLAGS) $(CPPFLAGS) $(PREPROC) $(SRCS) -o $(BUILDDIR)/$@
	
clean:
	rm $(BUILDDIR)/machina-32
test:
	./$(BUILDDIR)/machina-32



