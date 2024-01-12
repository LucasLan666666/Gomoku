CC = gcc

CFLAGS = -O3

CFLAGS2 = -Wall -Werror -g

SRCDIRS=src/AI src/basic src/evaluate src/forbidden_moves src/game_mode src/others

SOURCES=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

all:	
	$(CC) $(CFLAGS) -o gomoku $(SOURCES)

debug:
	$(CC) $(CFLAGS2) -o gomoku $(SOURCES)

clean:
	rm -f gomoku