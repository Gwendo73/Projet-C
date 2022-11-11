all : main clean

main: main.o image.o bmp.o
	gcc -o main main.o image.o bmp.o

main.o : main.c
	gcc -c -Wall main.c

image.o : image.c
	gcc -c -Wall image.c

bmp.o : bmp.c
	gcc -c -Wall bmp.c

clean:
ifeq ($(OS),Windows_NT)
	del /F *.o
else
	rm -f *.o
endif