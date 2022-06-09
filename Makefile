NAME	=	minishell


CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
DEBUG	=	-g3 -fsanitize=address -DDEBUG_FLAG=1
RM		=	rm -f

# parser source files
SRC		=	main.c\
			memory_management.c\
			parser/parser.c\
			parser/parser_error.c\
			parser/parse_command.c\
			parser/parse_redirect.c\
			parser/print_parsing_info.c\
			tokenizer/tokenizer.c\
			tokenizer/helper_functions.c\
			tokenizer/helper_functions_2.c\
			tokenizer/recognition_procedure_1.c\
			tokenizer/recognition_procedure_2.c\
			tokenizer/word_expansion.c
# builtin source files
SRC2	=	built_in/env.c\
			built_in/export.c\
			built_in/key_compare.c\
			built_in/set_env.c\
			built_in/check_key.c\
			built_in/delete_content.c\
			built_in/echo.c\
			built_in/exit.c\
			built_in/cd.c\
			built_in/ft_atoll.c\
			built_in/ft_split_first.c\
			built_in/unset.c
SRC		+=	$(SRC2)
SRC_DIR	=	src
SRC		:=	$(SRC:%=$(SRC_DIR)/%)
OBJ		=	$(SRC:%.c=%.o)

INCL	=	built_in/minishell.h\
			built_in/doubly_linked_list.h\
			built_in/libft.h\
			built_in/parser/parser.h\
			built_in/parser/token.h
INCL_DIR=	include
INCL	:=	$(INCL:%=$(INCL_DIR)/%)


LIB_ADD	=	-L.
LIBTARGET=	all

LIBFT	=	libft.a
LIBFT_DIR=	libft
LIB_ADD	+=	-lft
LIBS	+=	LIBFT.lib


DLLIST	=	libdlinkedlist.a
DLLIST_DIR=	doubly_linked_list
LIB_ADD	+=	-ldlinkedlist
LIBS	+=	DLLIST.lib

ifeq ($(DEBUG_FLAG), 1)
CFLAGS	+=	$(DEBUG)
LIBFLAGS= DEBUG_FLAG=1	
endif


libs: $(LIBS)
	$(MAKE) $(NAME)

all: $(NAME)

debug:
	$(MAKE) clean
	$(MAKE) DEBUG_FLAG=1 all

$(LIBS): %.lib:
	$(MAKE) -C $($*_DIR) $(LIBFLAGS) all
	@cp -p $($*_DIR)/$($*) .

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -lreadline $(LIB_ADD)

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCL_DIR)

clean:
	$(RM) $(OBJ)

fclean: clean $(LIBS:%=%.clean)
	$(RM) $($(LIBS:%.lib=%))
	$(RM) $(NAME)

$(LIBS:%=%.clean): %.lib.clean:
	$(RM) $($*)
	@$(MAKE) -C $($*_DIR) fclean
	$(RM) $*.lib

re: fclean
	$(MAKE) libs

.PHONY: all clean fclean re libs
