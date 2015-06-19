#————————————————————————————————————————————————————————
#
# Makefile for 
# Alexis Romero
# Last modified: 06/19/2015
#
#————————————————————————————————————————————————————————


ifeq ($(USER),jthaler)
	SHELL = /bin/sh
	PYTHIA8LOCATION = /Users/jthaler/hepsoft/pythia8209
	FASTJETLOCATION = /usr/local/bin/
endif

ifeq ($(USER),marcstudent)
	SHELL = /bin/sh
	PYTHIA8LOCATION = /Users/marcstudent/Desktop/pythia8209
endif


#Pythia Flags
PREFIX_LIB     = -L$(PYTHIA8LOCATION)/lib
PREFIX_INCLUDE = -I$(PYTHIA8LOCATION)/include


# Compilation flags (see ./configure --help for further documentation).
ENABLE_SHARED=false
CXX=g++
CXX_COMMON=-O2 -ansi -pedantic -W -Wall -Wshadow -fPIC
CXX_SHARED=-dynamiclib -flat_namespace -undefined suppress -Qunused-arguments
CXX_SONAME=-Wl,-dylib_install_name
LIB_SUFFIX=.dylib

# FASTJET3 configuration.
FASTJET3_USE=true
FASTJET3_BIN=/Users/marcstudent/Desktop/fastjet-3.1.2/build/bin
FASTJET3_INCLUDE=/Users/marcstudent/Desktop/fastjet-3.1.2/build/include
FASTJET3_LIB=/Users/marcstudent/Desktop/fastjet-3.1.2/build/lib


CXX_COMMON:= $(PREFIX_INCLUDE) $(CXX_COMMON) -Wl,-rpath $(PREFIX_LIB) -ldl -lpythia8

all: p_main01

# Phony targets -> all clean
.PHONY: all clean


# My main program (no external dependency) 
p_main01 : p_main01.cc
	$(CXX) $^ -o $@ $(CXX_COMMON)


# Clean.
clean:
	rm -f p_main*.o
