CC = g++
CPPFLAGS = -std=c++11 -Wall \
		   -I/usr/local/opt/opencv@3/include
LDFLAGS = -L/usr/local/opt/opencv@3/lib
LIBS = -lgtest -lpthread
SRC = ..
OBJ = ../obj
BIN = ../bin
TEST = ./

all: dirs $(BIN)/main

$(BIN)/main: $(OBJ)/main.o
	$(CC) $(CPPFLAGS) $< -o $@ $(LIBS)

$(OBJ)/main.o: $(TEST)/ut_main.cpp
	$(CC) $(CPPFLAGS) -c $^ -o $@ $(LIBS)

dirs:
	mkdir -p $(OBJ) $(BIN)

clean:
	rm -rf $(OBJ) $(BIN)

stat:
	wc $(SRC)/*
