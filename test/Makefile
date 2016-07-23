# Include dir: folder where header files are stored
IDIR =../include

# Source code files that must be linked
# to create the executable
CXX_SOURCES = ../src/LinearCongruentialGenerator.cpp #\
#              ../src/MIDTestDriver.cpp

# Object files are the same as source files,
# but with all the .cpp suffixes replaced with .o
OBJECTS = $(CXX_SOURCES:.cpp=.o)

# Header files
_HEADERS = LinearCongruentialGenerator.h
HEADERS = $(patsubst %,$(IDIR)/%,$(_HEADERS))

# Compiler
CXX = g++
# Pre-processor flags
CPPFLAGS = -I$(IDIR)
# Compiler flags
CXXFLAGS = -std=c++11 -Wall
# Linker
CC = $(CXX)

# all is the default rule
all: testsuite

# The executable depends on the object files
# It is made automagically using the LDFLAGS and LOADLIBES variables.
# The .o files are made automagically using the CXXFLAGS variable.

# Executable files for tests
CXX_EXECS = test_LinearCongruentialGenerator.cpp \
            test_MIDStub.cpp \
            test_MIDTestDriver.cpp

TESTS = test_LinearCongruentialGenerator \
        test_MIDStub #\
#        test_MIDTestDriver

testsuite: $(TESTS)

test_LinearCongruentialGenerator: test_LinearCongruentialGenerator.o $(OBJECTS)

test_MIDStub: test_MIDStub.o $(OBJECTS)

test_MIDTestDriver: test_MIDTestDriver.o $(OBJECTS)