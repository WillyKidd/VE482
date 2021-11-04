.DEFAULT_GOAL := all

CC = clang
CFLAGS = -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -Wconversion -Wvla
MAIN_SRC = src-main/list.c src-main/main.c src-main/plugin_manager.c
TXT_SRC = src-plugin-txt/sort.c src-plugin-txt/ui.c src-main/list.c src-main/plugin_manager.c
CSV_SRC = src-plugin-csv/sort.c src-plugin-csv/ui.c src-main/list.c src-main/plugin_manager.c
MAIN = l6
MAINMC = l6_memory_check
MAINMC_FLAGS = -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=integer
PLUGIN_TXT = ./plugins/txt.so
PLUGIN_CSV = ./plugins/csv.so
.PHONY: clean

all: $(MAIN) $(MAINMC) $(PLUGIN_TXT) $(PLUGIN_CSV)
	@echo "l6 successfully constructed :D"

$(MAIN): $(MAIN_SRC)
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN_SRC) -ldl

$(MAINMC): $(MAIN_SRC)
	$(CC) $(CFLAGS) $(MAINMC_FLAGS) -o $(MAINMC) $(MAIN_SRC) -ldl

$(PLUGIN_TXT): $(TXT_SRC)
	$(CC) $(CFLAGS)	-shared -fPIC -o $(PLUGIN_TXT) $(TXT_SRC)

$(PLUGIN_CSV): $(CSV_SRC)
	$(CC) $(CFLAGS) -shared -fPIC -o $(PLUGIN_CSV) $(CSV_SRC)

clean:
	rm *.o *.a $(MAIN) $(MAINMC) $(PLUGIN_TXT) $(PLUGIN_CSV) *.tar
