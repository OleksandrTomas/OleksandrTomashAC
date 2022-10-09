TARGET= MyProject
CC=gcc
$(TARGET) : main.o my_lib.o
	$(CC) main.o my_lib.o -o $(TARGET)
main.o : main.c
	$(CC) -c main.c -o main.o
my_lib.o : my_lib.c
	$(CC) -c my_lib.c -o my_lib.o
clean : 
	rm -rf *.o $(TARGET)

