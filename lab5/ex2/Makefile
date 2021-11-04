CC = clang
CFLAGS = -std=gnu11 -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -g
LIST_SRC = *.c
LIST = LIST
LISTMC = LIST_memory_check
LISTMC_FLAGS = -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=integer
PHONY: clean
all: $(LIST) $(LISTMC)
	@echo LIST successfully constructed

$(LIST): $(LIST_SRC)
	$(CC) $(CFLAGS) -o $(LIST) $(LIST_SRC)

$(LISTMC) : $(LIST_SRC)
	$(CC) $(CFLAGS) $(LISTMC_FLAGS) -o $(LISTMC) $(LIST_SRC)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o *.a *~ $(LIST) $(LISTMC) *.txt
