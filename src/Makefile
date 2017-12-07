INCDIR = ./src
EXTRA_CFLAGS += $(DEBFLAGS)
EXTRA_CFLAGS += -I$(INCDIR)

all: WordStatistics

WordStatistics: ./src/main.cpp
	mkdir -p bin
	g++ -std=c++11 ./src/main.cpp -o ./bin/WordStatistics -w

clean:
	rm -f ./bin/WordStatistics
	rm -rf bin
	rm -f ./*.json