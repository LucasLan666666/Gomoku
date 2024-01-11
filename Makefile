CC = gcc

CFLAGS = -O3

SRCDIRS=src/AI src/basic src/evaluate src/forbidden_moves src/game_mode

SOURCES=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

all:	
	$(CC) $(CFLAGS) -g -o gomoku $(SOURCES)
