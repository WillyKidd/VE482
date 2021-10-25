CC = clang
CFLAGS = -std=gnu11 -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -Wconversion -Wvla
SRC = *.c
LIST = list
LISTMC = list_memory_check
LISTMC_FLAGS = -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=integer
PHONY: clean
all: $(LIST) $(LISTMC)
	@echo list successfully constructed

$(LIST): $(SRC)
	$(CC) $(CFLAGS) -o $(LIST) $(SRC)

$(LISTMC) : $(SRC)
	$(CC) $(CFLAGS) $(LISTMC_FLAGS) -o $(LISTMC) $(SRC)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o *.a *.txt *~ $(LIST) $(LISTMC)