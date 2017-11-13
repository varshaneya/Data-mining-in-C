CC=gcc
FLAGS1=-c
TARGET=myShell
SOURCE = myShell.o errorHandlers.o

$(TARGET):	$(SOURCE)
	$(CC) -o $@ $?
	rm *.o
myShell.o:	myShell.c apue.h
	$(CC) $(FLAGS1) $?
errorHandlers.o:	errorHandlers.c apue.h
	$(CC) $(FLAGS1) $?
clean:
	rm *.o
