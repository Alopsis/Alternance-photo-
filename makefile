CC= g++
CFLAGS= -I.. -Wall -Wextra -Wfatal-errors -Werror=unknown-pragmas -Werror=unused-label -Wshadow -std=c++11 -pedantic -Dcimg_use_vt100 -Dcimg_display=1
LDLIBS=-lpthread -lX11 -lm

main: main.cpp couleurs.cpp divers.cpp histo.cpp
	$(CC) -o $@ $+ $(CFLAGS) $(LDLIBS)


couleurs.o: couleurs.h couleurs.cpp
	$(CC) $(CFLAGS) -c couleurs.cpp

divers.o: divers.h divers.cpp
	$(CC) $(CFLAGS) -c divers.cpp

histo.o: histo.h histo.cpp
	$(CC) $(CFLAGS) -c histo.cpp

clean: 
	rm -f *.o main 