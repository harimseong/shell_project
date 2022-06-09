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
SRC_DIR	=	src
SRC		:=	$(SRC:%=$(SRC_DIR)/%)
# builtin source files
SRC2	=	env.c\
			export.c\
			key_compare.c\
			set_env.c\
			check_key.c\
			delete_content.c\
			echo.c\
			exit.c\
			cd.c\
			ft_atoll.c\
			ft_split_first.c\
			unset.c
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
	$(MAKE) all

.PHONY: all clean fclean re libs
