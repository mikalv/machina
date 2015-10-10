include ./config/Makefile.config
include ./config/Makefile.rules

default: all

.PHONY: clean
.PHONY: doc

machina:
	-make --no-print-directory -f ./config/Makefile clean
	make --no-print-directory -f ./config/Makefile
	
test:
	make --no-print-directory -f ./config/Makefile test

	

doc: Doxyfile
	@rm -rf doc
	@mkdir doc
	doxygen Doxyfile

all:
	make --no-print-directory machina
	make --no-print-directory doc
	
clean:
	make --no-print-directory -f ./config/Makefile clean