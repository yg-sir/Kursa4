.PHONY: all clean format doxy test

CXX = g++
CXXFLAGS = -O2 -Wall -DNDEBUG -std=c++17
LDFLAGS = -lcryptopp -lboost_program_options -lUnitTest++ -pthread

TARGET = Server
SOURCES = Connection_of_client.cpp Calculate.cpp DatabaseConnector.cpp Interface.cpp Logger.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

TEST_SOURCES = Connection_of_client.cpp Calculate.cpp DatabaseConnector.cpp Interface.cpp Logger.cpp test.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_TARGET = test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_OBJECTS)
	$(CXX) $(TEST_OBJECTS) $(LDFLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)

format:
	astyle *.cpp *.h

doxy:
	doxygen

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o
