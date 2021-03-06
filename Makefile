CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: deepimpact

atorres.o: atorres.cpp atorres.h
	g++ -c atorres.cpp -Wall $(LFLAGS)

bayapantecat.o: bayapantecat.cpp bayapantecat.h
	g++ -c bayapantecat.cpp -Wall $(LFLAGS)

imacias.o: imacias.cpp imacias.h
	g++ -c imacias.cpp -Wall $(LFLAGS)
	
jflores.o: jflores.cpp jflores.h
	g++ -c jflores.cpp -Wall $(LFLAGS)

deepimpact: asteroids.cpp timers.cpp atorres.o bayapantecat.o imacias.o jflores.o
	g++ $(CFLAGS) asteroids.cpp timers.cpp jflores.o bayapantecat.o \
	imacias.o atorres.o libggfonts.a credits.h images.h -Wall -Wextra $(LFLAGS) -o deepimpact

clean:
	rm -f deepimpact
	rm -f board.txt
	rm -f *.o

