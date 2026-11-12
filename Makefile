CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Iinclude

ifeq ($(OS),Windows_NT)
EXEEXT = .exe
RUN_PREFIX =
CLEAN_COMMAND = cmd /C del /Q $(APP) $(TEST) 2>NUL
else
EXEEXT =
RUN_PREFIX = ./
CLEAN_COMMAND = rm -f $(APP) $(TEST)
endif

APP = agenda$(EXEEXT)
TEST = teste_exec$(EXEEXT)

.PHONY: all test run clean

all: $(APP)

$(APP): src/main.c src/avl.c include/avl.h
	$(CC) $(CFLAGS) src/main.c src/avl.c -o $@

$(TEST): tests/teste.c src/avl.c include/avl.h
	$(CC) $(CFLAGS) tests/teste.c src/avl.c -o $@

test: $(TEST)
	$(RUN_PREFIX)$(TEST)

run: $(APP)
	$(RUN_PREFIX)$(APP)

clean:
	-$(CLEAN_COMMAND)
