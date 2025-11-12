CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = mySA
OBJS = mySA.o readvader.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

mySA.o: mySA.c readvader.h
readvader.o: readvader.c readvader.h

clean:
	rm -f $(TARGET) $(OBJS)
