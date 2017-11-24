
CC = g++-7
SRC_DIR = src/
INCLUDE_DIR = include/

OUTFILE = tic

COMPILE_FLAGS = -lncurses -std=c++14 -Wall -Wextra -O3

# -------------------------------------------------

all: bin compile build

run: bin compile build
	./tic

bin:
	mkdir bin

compile:
	@rm bin/*.o; \
	cd $(SRC_DIR); \
	$(CC) -c *.cpp -I../include; \
	mv *.o ../bin; \
	cd -;

build:
	$(CC) bin/*.o $(COMPILE_FLAGS) -o $(OUTFILE)

clean:
	rm -rf bin

.PHONY: all compile build clean run
