CC= g++
CFLAGS= -I.. -Wall -Wextra -Wfatal-errors -Werror=unknown-pragmas -Werror=unused-label -Wshadow -std=c++11 -pedantic -Dcimg_use_vt100 -Dcimg_display=1
LDLIBS=-lpthread -lX11 -lm

main: main.cpp
	$(CC) -o $@ $+ $(CFLAGS) $(LDLIBS)
