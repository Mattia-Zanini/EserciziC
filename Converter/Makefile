#make file - this is a comment section

TARGET = main

all: # compile the code
	@gcc -c test/functions.c debug/log.c
	@gcc $(TARGET).c functions.o log.o -o $(TARGET)

clean: # clean trash file
	@find . -type f ! -name 'Makefile' ! -name '*.c' ! -name '*.txt' ! -name '*.dg' ! -name '*.h' ! -name '*.log' -delete