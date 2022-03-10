#make file - this is a comment section

TARGET = main
TARGET_2 = functions
files = ("*.c")

all: # compile the code
	@gcc -c test/$(TARGET_2).c
	@gcc $(TARGET).c $(TARGET_2).o -o $(TARGET)

clean: # clean trash file
	@find . -type f ! -name 'Makefile' ! -name '*.c' ! -name '*.txt' ! -name '*.dg' ! -name '*.h' -delete