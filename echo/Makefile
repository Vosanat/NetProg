
.PHONY: all debug 

CXXFLAGS 	  =  -std=c++11 -Wall -DNDEBUG
EXEC  		=  server
SOURCE        =  $(wildcard *.cpp) 

all: debug 

debug: $(EXEC)

$(EXEC): main.cpp
	g++ $(CXXFLAGS) main.cpp -o $(EXEC) 

clean:
	rm -f $(EXEC) 

