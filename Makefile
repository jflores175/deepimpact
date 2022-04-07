CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: deepimpact

imacias: imacias.cpp
	g++ -c imacias.cpp -oimacias -Wall $(LFLAGS)

atorres.o: atorres.h
	g++ -c atorres.cpp -Wall $(LFLAGS)

bayapantecat: bayapantecat.cpp bayapantecat.h
	g++ -c bayapantecat.cpp -Wall $(LFLAGS)

deepimpact: asteroids.cpp timers.cpp atorres.o
	g++ $(CFLAGS) asteroids.cpp timers.cpp jflores.cpp bayapantecat.cpp \
	imacias.cpp atorres.cpp libggfonts.a credits.h images.h -Wall -Wextra $(LFLAGS) -o deepimpact

clean:
	rm -f deepimpact
	rm -f *.o

