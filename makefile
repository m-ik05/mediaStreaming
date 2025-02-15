CC=g++
CFLAGS=-I
DEPS=header.h

header: testing.cpp streaming.cpp user.cpp coucon.cpp
	$(CC) -o testing testing.cpp streaming.cpp user.cpp coucon.cpp