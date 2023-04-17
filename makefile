game: main.o image.o perso.o
		gcc main.o image.o perso.o -o game -lSDL -lSDL_image -g

main.o: main.c
		gcc -c main.c -g

image.o: image.c
		gcc -c image.c -g

perso.o: perso.c
		gcc -c perso.c -g