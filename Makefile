include ./config/Makefile.config
include ./config/Makefile.rules

default: all

.PHONY: clean
.PHONY: doc

machina-64:
	-make --no-print-directory -f ./config/machina_arch_64/Makefile clean
	make --no-print-directory -f ./config/machina_arch_64/Makefile
	
machina-32:
	-make --no-print-directory -f ./config/machina_arch_32/Makefile clean
	make --no-print-directory -f ./config/machina_arch_32/Makefile
	
test-64:
	make --no-print-directory -f ./config/machina_arch_64/Makefile test
	
test-32:
	make --no-print-directory -f ./config/machina_arch_32/Makefile test

	

doc: Doxyfile
	@rm -rf doc
	@mkdir doc
	doxygen Doxyfile

all:
	make --no-print-directory machina-64
	make --no-print-directory machina-32
	make --no-print-directory doc
	
clean:
	make --no-print-directory -f ./config/machina_arch_64/Makefile clean
	make --no-print-directory -f ./config/machina_arch_32/Makefile clean