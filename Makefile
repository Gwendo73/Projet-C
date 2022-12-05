all : main clean

main: main.o image.o bmp.o calculation.o gcode.o
	gcc -o main main.o image.o bmp.o calculation.o gcode.o

main.o : main.c
	gcc -c -Wall main.c

image.o : image.c
	gcc -c -Wall image.c

bmp.o : bmp.c
	gcc -c -Wall bmp.c

calculation.o : calculation.c
	gcc -c -Wall calculation.c

gcode.o : gcode.c
	gcc -c -Wall gcode.c

clean:
ifeq ($(OS), Windows_NT)
	rm -f *.o
else
	rm -f *.o
endif