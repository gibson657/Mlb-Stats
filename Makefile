CXX      := g++
CXXFLAGS := -Wall -O0 -g -std=c++1y

OUT := p1

SRC := MLB.cpp
OBJ := $(SRC:%.cpp=%.o)

.PHONY: all clean

all: $(OUT) randSeq intRunTime

$(OUT): $(OBJ)
    $(CXX) -o $@ $^

$(OBJ): %.o: %.cpp
    $(CXX) -o $@ $(CXXFLAGS) -c $<
    
randSeq: randSeq.cc
    $(CXX) -o $@ $(CXXFLAGS) $<
    
intRunTime: intRunTime.cpp
    $(CXX) -o $@ $(CXXFLAGS) $<

clean:
    @-rm -f $(OUT)
    @-rm -f $(OBJ)