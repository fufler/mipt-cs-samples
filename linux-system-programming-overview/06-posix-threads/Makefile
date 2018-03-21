CXX := clang++
CXXFLAGS := -Wall -Wextra -Wpedantic -Werror -std=c++14 -pthread

OBJS := $(patsubst %.cpp,%.bin,$(wildcard *.cpp))

all: $(OBJS)

%.bin: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJS)

.PHONY: all clean

