CC = gcc
EXEC = main
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
#CFLAGS = -Wall -Werror -Wextra

all : $(EXEC)

%.o : %.c
	$(CC) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^

clean :
	rm -rf $(OBJ)

mrproper : clean
	rm -rf $(EXEC)