# PYTHIA configuration file.
# Generated on Sat Jun 13 21:24:16 EDT 2015 with the user supplied options:

# Install directory prefixes.
ifneq ("$(wildcard ../lib/libpythia8.a)","")
	PREFIX_BIN=.../bin
	PREFIX_INCLUDE=.../include
	PREFIX_LIB=.../lib
	PREFIX_SHARE=.../share/Pythia8
endif

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