#making make file here

#defining compiler
CC=gcc
#defining files
FILES= poker.c cardDeck.c hands.c pokerRank.c testPokerRank.c
#defining executable
OUT_EXEC=myexec.out

BUILD: $(FILES)
	$(CC) $(FILES) -o $(OUT_EXEC)

CLEAN:
	-rm -f *.out core

REBUILD:
	clean build
