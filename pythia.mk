#————————————————————————————————————————————————————————
#
# Makefile for 
# Alexis Romero
# Last modified: 06/19/2015
#
#————————————————————————————————————————————————————————

# Use make -f pythia.mk filename

# Include pMakefile.inc -> configuration 
-include pMakefile.inc

# For GZIP.
ifeq ($(GZIP_USE),true)
  CXX_COMMON+= -DGZIPSUPPORT -I$(GZIP_INCLUDE)
  CXX_COMMON+= -L$(GZIP_LIB) -Wl,-rpath $(GZIP_LIB) -lz
endif

# Shortcut to Pythia /lib and /include libraries
ifneq ("$(wildcard /Users/marcstudent/Desktop/pythia8209/lib/libpythia8.a)","")
  PREFIX_LIB=/Users/marcstudent/Desktop/pythia8209/lib
  PREFIX_INCLUDE=/Users/marcstudent/Desktop/pythia8209/include
endif
CXX_COMMON:=-I$(PREFIX_INCLUDE) $(CXX_COMMON) -Wl,-rpath $(PREFIX_LIB) -ldl

# Secondary expansion for rules
.SECONDEXPANSION:

# Phony targets -> all clean
.PHONY: all clean

# pMakefile.inc configuration
pMakefile.inc:
	$(error Error: PYTHIA must be configured, please run "./configure"\
                in the top PYTHIA directory)

# Shortcut to Pythia libraries 
$(PREFIX_LIB)/libpythia8.a :
	$(error Error: PYTHIA must be built, please run "make"\
                in the top PYTHIA directory)

# My main program (no external dependency) 
p_main% : p_main%.cc $(PREFIX_LIB)/libpythia8.a
	$(CXX) $^ -o $@ $(CXX_COMMON)

# Include FASTJET3.
p_main%: p_main%.cc $(PREFIX_LIB)/libpythia8.a
ifeq ($(FASTJET3_USE),true)
	$(CXX) $^ -o $@ -I$(FASTJET3_INCLUDE) $(CXX_COMMON)\
	 -L$(FASTJET3_LIB) -Wl,-rpath $(FASTJET3_LIB) -lfastjet
else
	@echo "Error: $@ requires FASTJET3"
endif

# Clean.
clean:
	rm -f p_main*.o
