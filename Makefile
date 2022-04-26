CC=gcc
OBJS=AsciiArtTool.o RLEList.o
EXEC=prog
DEBUG=#now empty,  assign -g for debug
CFLAGS=-std=c99 -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS) $(CC) $(DEBUG_FLAG) $(OBJS) -o $@

AsciiArtTool.o : ./tool/AsciiArtTool.c ./tool/AsciiArtTool.h ./tool/main.c
RLEList.o : RLEList.c RLEList.h

clean: rm -f $(OBJS) $(EXEC)
