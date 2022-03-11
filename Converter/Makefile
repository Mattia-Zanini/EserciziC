#make file - this is a comment section
# @find . -type f ! -name 'Makefile' -delete //per non eliminare il file Makefile

TARGET = main

all: # compile the code
	@gcc -c test/err.c debug/log.c
	@gcc $(TARGET).c err.o log.o -o $(TARGET)
	@find . -type f -name '*.o' -delete
	@find . -type f -name '*.out' -delete

clean: # clean trash file
	@find . -type f -name '$(TARGET)' -delete
	@find . -type f -name '*.o' -delete
	@find . -type f -name '*.out' -delete