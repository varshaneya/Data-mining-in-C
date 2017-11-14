CC = gcc
FLAGS = -Wall -c
OBJECTS =  dfsDir.o errorHandlers.o myls.o
TARGET = myls

$(TARGET):	$(OBJECTS)
	$(CC) -o $@ $?
errorHandlers.o:	errorHandlers.c apue.h
	$(CC) $(FLAGS) $?
dfsDir.o:	dfsDir.c apue.h
	$(CC) $(FLAGS) $?
myls.o:	myls.c apue.h
	$(CC) $(FLAGS) $?
clean:
	rm *.o
