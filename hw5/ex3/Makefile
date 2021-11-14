.DEFAULT_GOAL := all

CC = clang++
CFLAGS = -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -Wconversion -Wvla
MAIN = banker
MAIN_SRC = banker.cpp
.PHONY : clean

all: $(MAIN)
	@echo "banker successfully constructed"

$(MAIN): $(MAIN_SRC)
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN_SRC)

clean:
	rm $(MAIN) *.o main
