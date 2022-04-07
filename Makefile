CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: deepimpact

imacias.o: imacias.cpp imacias.h
	g++ -c imacias.cpp -Wall $(LFLAGS)

atorres.o: atorres.cpp atorres.h
	g++ -c atorres.cpp -Wall $(LFLAGS)

jflores.o: jflroes.cpp jflores.h
	g++ -c jflores.cpp -Wall $(LFLAGS)

deepimpact: asteroids.cpp timers.cpp atorres.o
	g++ $(CFLAGS) asteroids.cpp timers.cpp jflores.cpp bayapantecat.cpp \
	imacias.cpp atorres.cpp libggfonts.a credits.h images.h -Wall -Wextra $(LFLAGS) -o deepimpact

clean:
	rm -f deepimpact
	rm -f *.o

