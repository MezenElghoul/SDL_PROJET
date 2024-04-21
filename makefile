jeuu:backg.o perso.o jeu.c Enigme
	gcc *.o jeu.c -o jeu -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
	rm *.o
	./jeu
backg.o:
	gcc ./background/backg.c -c
perso.o:
	gcc ./player/joueur.c -c
Enigme:
	gcc ./enigme/*.c -c
remove:
	rm *.o


compile:
	gcc *.c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g