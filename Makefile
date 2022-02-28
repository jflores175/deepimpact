CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: deepimpact

deepimpact: asteroids.cpp timers.cpp 
	g++ $(CFLAGS) asteroids.cpp timers.cpp jflores.cpp bayapantecatl.cpp \
	imacias.cpp atorres.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o deepimpact

clean:
	rm -f deepimpact
	rm -f *.o

