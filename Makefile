CC    := gcc
CFLAG := -pthread -g -o
SOURCE:= ./main.c 
TARGET:= ./prog1

all: main
	$(TARGET) 4 3 1 7 4
main:
	$(CC) $(SOURCE) $(CFLAG) $(TARGET)
clean:
	rm $(TARGET)
