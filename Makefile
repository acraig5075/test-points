CC = g++
RM = rm
CFLAGS = -g -Wall
TARGET = tp
LIBS = -L/usr/lib -lboost_program_options

$(TARGET): main.o TestPoints.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o TestPoints.o $(LIBS)
main.o: main.cpp TestPoints.h
	$(CC) $(CFLAGS) -c main.cpp
TestPoints.o: TestPoints.cpp
	$(CC) $(CFLAGS) -c TestPoints.cpp

clean:
	$(RM) main.o TestPoints.o
