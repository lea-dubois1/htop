CC = gcc
EXEC = main
CFLAGS = -Wall -Werror -Wextra -g3
OBJDIR = obj/
SRCDIR = src/
SRC = dataManager.c displayHandler.c main.c
SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJ = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -lncurses -o $@ $^

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ)

mrproper : clean
	rm -rf $(EXEC)