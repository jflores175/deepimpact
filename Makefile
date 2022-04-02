CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: deepimpact

atorres.o: atorres.o atorres.h
	g++ -c atorres.cpp -Wall $(LFLAGS)

deepimpact: asteroids.cpp timers.cpp atorres.o
	g++ $(CFLAGS) asteroids.cpp timers.cpp jflores.cpp bayapantecat.cpp \
	imacias.cpp atorres.o libggfonts.a credits.h images.h -Wall -Wextra $(LFLAGS) -o deepimpact

clean:
	rm -f deepimpact
	rm -f *.o

