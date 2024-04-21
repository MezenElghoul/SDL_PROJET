enigme:MainEnigme.o enigme.o
	gcc MainEnigme.o enigme.o -o enigme -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
	rm *.o
	./enigme
MainEnigme.o:MainEnigme.c
	gcc MainEnigme.c -c  -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
enigme.o:enigme.c
	gcc enigme.c -c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
delete:
	rm *.o
run:enigme
	./enigme