CC = g++

TARGET = Q5

all: $(TARGET)

$(TARGET): main.o libmodules.a
	$(CC) main.o -L. -lmodules -o $(TARGET)

libmodules.a: string_fxn.o array_fxn.o
	ar rcs libmodules.a string_fxn.o array_fxn.o

main.o: main.cpp string_fxn.h array_fxn.h
	$(CC) -c main.cpp

string_fxn.o: string_fxn.cpp string_fxn.h
	$(CC) -c string_fxn.cpp

array_fxn.o: array_fxn.cpp array_fxn.h
	$(CC) -c array_fxn.cpp

clean:
	rm -f *.o *.a $(TARGET)
