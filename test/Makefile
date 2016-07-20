# Include dir: folder where header files are stored
IDIR =../include

# Executable file
EXEC = test_LinearCongruentialGenerator

# Source code files that must be linked
# to create the executable
CXX_SOURCES = ../src/LinearCongruentialGenerator.cpp \
              test_LinearCongruentialGenerator.cpp

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


# The executable depends on the object files
# It is made automagically using the LDFLAGS and LOADLIBES variables.
# The .o files are made automagically using the CXXFLAGS variable.
$(EXEC): $(OBJECTS)
