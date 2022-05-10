NAME	= libdlinkedlist.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

SRC		= dlinkedlist.c\
		  dlinkedlist_util.c\
		  dlinkedlist_peek.c\
		  dlinkedlist_cur.c\
		  dlinkedlist_dup.c
OBJ		= $(SRC:%.c=%.o)

INCLUDE	= dlinkedlist.h
INCL_DIR= ../include

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -I. -I$(INCL_DIR)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
