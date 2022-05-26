NAME	=	minishell


CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
DEBUG	=	-g3 -fsanitize=address
RM		=	rm -f

# parser source files
SRC		=	main.c\
			memory_management.c\
			parser/parser.c\
			parser/parse_command.c\
			parser/parse_redirect.c
#			parser/tokenizer.c
SRC_DIR	=	src
SRC		:=	$(SRC:%=$(SRC_DIR)/%)
# builtin source files
SRC2	=	env.c\
			export.c\
			key_compare.c\
			builtin.c
SRC2_DIR=	cmd_temp
SRC2	:=	$(SRC2:%=$(SRC2_DIR)/%)
SRC		+=	$(SRC2)
OBJ		=	$(SRC:%.c=%.o)

INCL	=	minishell.h\
			doubly_linked_list.h\
			libft.h\
			parser/parser.h\
			parser/token.h
INCL_DIR=	include
INCL	:=	$(INCL:%=$(INCL_DIR)/%)


LIBFLAGS=	-L.

LIBFT	=	libft.a
LIBFT_DIR=	libft
LIBFLAGS+=	-lft
LIBS	+=	LIBFT.lib


DLLIST	=	libdlinkedlist.a
DLLIST_DIR=	doubly_linked_list
LIBFLAGS+=	-ldlinkedlist
LIBS	+=	DLLIST.lib

ifeq ($(DEBUG_FLAG), 1)
CFLAGS	+=	$(DEBUG)
endif


all:
	$(MAKE) $(NAME)

debug:
	$(MAKE) clean
	$(MAKE) DEBUG_FLAG=1 all

$(NAME): $(LIBS) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -lreadline $(LIBFLAGS)

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCL_DIR)

$(LIBS): %.lib:
	@$(MAKE) -C $($*_DIR) all
	mv $($*_DIR)/$($*) .

clean:
	$(RM) $(OBJ)

fclean: clean $(LIBS:%=%.clean)
	$(RM) $($(LIBS:%.lib=%))
	$(RM) $(NAME)

$(LIBS:%=%.clean): %.lib.clean:
	$(RM) $($*)
	@$(MAKE) -C $($*_DIR) fclean

re: fclean
	$(MAKE) all

.PHONY: all clean fclean libclean re
