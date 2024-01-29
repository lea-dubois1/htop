CC = gcc
EXEC = main
CFLAGS = -Wall -Werror -Wextra
OBJDIR = obj/
SRCDIR = src/
SRC = $(wildcard $(SRCDIR)*.c)
OBJ = $(SRC:.c=.o)

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^
	cp $(SRCDIR)*.o $(OBJDIR)
	rm -rf $(SRCDIR)*.o

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ)

mrproper : clean
	rm -rf $(EXEC)