CXX := clang++
CXXFLAGS := -Wall -std=c++14

OBJS := $(patsubst %.cpp,%.bin,$(wildcard *.cpp))

all: $(OBJS)

%.bin: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJS)

.PHONY: all clean

