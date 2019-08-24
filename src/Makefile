PROGRAMS = tendril
LIBS = tendril.a
TESTS = board_test capi_test cell_test

COMPILE = g++ -g -O0 -Wall -std=c++17

all: $(PROGRAMS) $(LIBS)

clean:
	rm -f $(PROGRAMS) $(TESTS) *.o

check: $(TESTS)
	set -e; \
	for t in $(TESTS); do \
		echo "Testing $$t..."; \
		./$$t; \
	done

board_test: board_test.cpp board.o
	$(COMPILE) -o $@ $^

cell_test: cell_test.cpp cell.o
	$(COMPILE) -o $@ $^

game_test: game_test.cpp game.o
	$(COMPILE) -o $@ $^

OBJS = \
	   board.o \
	   boardloader.o \
	   cell.o \
	   game.o \
	   player.o \
	   playerview.o \
	   renderer.o \
	   tendril.o \
	   terminalrenderer.o \
	   #
tendril: $(OBJS)
	$(COMPILE) -o $@ $^

%.o: %.cpp %.h
	$(COMPILE) -c -o $@ $<

tendril.a: $(OBJS) capi.o
	ar cr $@ $^

capi_test: capi_test.c tendril.a
	gcc -Wall -o $@ $^ -lstdc++
