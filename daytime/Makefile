# Усложненный make-file.  Введены переменные для параметров компиляции и исполняемых файлов

.PHONY: all debug release 

RELEASE_FLAGS = -O2 -Wall -DNDEBUG
DEBUG_FLAGS   = -g -O0 -Wall
RELEASE_EXEC  =  client
DEBUG_EXEC    =  client-dbg
SOURCE        =  $(wildcard *.cpp)
MASS		 =	 client.cpp

all: debug release

debug: $(DEBUG_EXEC)

$(DEBUG_EXEC): MASS
	g++ $(DEBUG_FLAGS) MASS -o $(DEBUG_EXEC) 

release: $(RELEASE_EXEC)

$(RELEASE_EXEC): MASS
	g++ $(RELEASE_FLAGS) MASS -o $(RELEASE_EXEC)

clean:
	rm -f $(RELEASE_EXEC) $(DEBUG_EXEC)

