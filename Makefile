TARGET=prog3
CFLAGS=-Wall
CC=gcc

all: $(TARGET)
	
$(TARGET): main.o mybarrier.o
	$(CC) $(CFLAGS) -o $@ main.o mybarrier.o
	
main.o: main.c mybarrier.h 
	$(CC) $(CFLAGS) -c main.c
		
mybarrier.o: mybarrier.c mybarrier.h
	$(CC) $(CFLAGS) -c $*.c
		
clean:
	rm -rf *.o *.a *.itm $(TARGET)