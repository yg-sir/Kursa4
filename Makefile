.PHONY: all clean format

CXX=g++
CXXFLAGS=-O2 -Wall -DNDEBUG -std=c++17
LDFLAGS= -lcryptopp -lboost_program_options -lUnitTest++
PROJECT = Server
SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.h)
OBJECTS := $(SOURCES:%.cpp=%.o)

all : $(PROJECT)

$(PROJECT) : $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@
	rm -f *.o *.orig

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJECTS) : $(HEADERS)

format:
	astyle *.cpp *.h
doxy:
	doxygen
clean:
	rm -f $(PROJECT) *.o *.orig
