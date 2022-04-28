CC=gcc
OBJS=tool/AsciiArtTool.o tool/main.o RLEList.o
EXEC=AsciiArtTool
DEBUG=#now empty,  assign -g for debug
CFLAGS=-std=c99 -I/home/mtm/public/2122b/ex1 -Itool -Wall -Werror -pedantic-errors -DNDEBUG $(DEBUG)

$(EXEC) : $(OBJS) 
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

AsciiArtTool.o : tool/AsciiArtTool.c RLEList.h tool/AsciiArtTool.h
main.o : tool/main.c RLEList.h tool/AsciiArtTool.h
RLEList.o : RLEList.c RLEList.h

clean: 
	rm -f $(OBJS) $(EXEC)
