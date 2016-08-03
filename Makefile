# Include dir: folder where header files are stored
IDIR = include
# Source dir: folder where source code files are stored
SRCDIR = src
# Test dir: folder where test executables are stored
TESTDIR = test

# Source code files that must be linked
# to create the executable
_CXX_SOURCES = LinearCongruentialGenerator.cpp
CXX_SOURCES = $(patsubst %,$(SRCDIR)/%,$(_CXX_SOURCES))

# Object files are the same as source files,
# but with all the .cpp suffixes replaced with .o
OBJECTS = $(CXX_SOURCES:.cpp=.o)

# Header files
_HEADERS = LinearCongruentialGenerator.h \
           MIDStub.h \
           MIDTestDriver.h
HEADERS = $(patsubst %,$(IDIR)/%,$(_HEADERS))

# Source files for tests
_CXX_TESTSOURCES = test_LinearCongruentialGenerator.cpp \
                   test_MIDStub.cpp \
                   test_MIDTestDriver.cpp
CXX_TESTSOURCES = $(patsubst %,$(TESTDIR)/%,$(_CXX_TESTSOURCES))

O_TESTSOURCES = $(CXX_TESTSOURCES:.cpp=.o)

# Executable files for tests
#TESTS = test_LinearCongruentialGenerator \
#        test_MIDStub #\
#        test_MIDTestDriver
TESTS = $(_CXX_TESTSOURCES:.cpp=)
TESTEXECS =  $(patsubst %,$(TESTDIR)/%,$(TESTS))

# Compiler
CXX = g++
# Pre-processor flags
CPPFLAGS = -I$(IDIR)
# Compiler flags
CXXFLAGS = -std=c++11 -Wall
# Linker
CC = $(CXX)

# Customising the default suffix rule for C++ sources
# in order to compile also in case of changes in the headers
%.o: %.cpp $(HEADERS)
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

# Test dir suffix rule
%: $(TESTDIR)/%.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $(TESTDIR)/$@

# all is the default rule
all: testsuite

# The executable depends on the object files
# It is made automagically using the LDFLAGS and LOADLIBES variables.
# The .o files are made automagically using the CXXFLAGS variable.

testsuite: $(TESTS)

test_LinearCongruentialGenerator: $(TESTDIR)/test_LinearCongruentialGenerator.o $(OBJECTS)

test_MIDStub: $(TESTDIR)/test_MIDStub.o $(OBJECTS)

test_MIDTestDriver: $(TESTDIR)/test_MIDTestDriver.o $(OBJECTS)

.PHONY: clean

clean:
	$(RM) $(OBJECTS) $(O_TESTSOURCES) $(TESTEXECS)