PROGRAMS = tendril
TESTS = cell_test board_test

COMPILE = g++ -Wall -std=c++11

all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS) $(TESTS)

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

tendril: board.o cell.o game.o tendril.o
	$(COMPILE) -o $@ $^

%.o: %.cpp %.h
	$(COMPILE) -c -o $@ $<
