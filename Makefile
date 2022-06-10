NAME	=	minishell


CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
DEBUG	=	-g3 -fsanitize=address -DDEBUG_FLAG=1
RM		=	rm -f

# parser source files
SRC		=	main.c\
			read_pipeline.c\
			execute_command.c\
			execute_helper_func.c\
			delete_command_list.c\
			minishell_initialize.c\
			parser/parser.c\
			parser/parser_error.c\
			parser/parse_command.c\
			parser/parse_redirect.c\
			parser/print_parsing_info.c\
			tokenizer/tokenizer.c\
			tokenizer/token_helper_func.c\
			tokenizer/recognition_procedure_1.c\
			tokenizer/recognition_procedure_2.c\
			tokenizer/word_expansion.c\
			built_in/env.c\
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
SRC_DIR	=	src
SRC		:=	$(SRC:%=$(SRC_DIR)/%)
OBJ		=	$(SRC:%.c=%.o)

INCL	=	minishell.h\
			doubly_linked_list.h\
			libft.h\
			cmd.h\
			parser/parser.h\
			parser/token.h\
			parser/token_recognition.h
INCL_DIR=	include
INCL	:=	$(INCL:%=$(INCL_DIR)/%)


LIB_ADD	=	-L.
LIBTARGET=	all

# NOTE: library order (-ldlinkedlist and -lft) can be problem
DLLIST	=	libdlinkedlist.a
DLLIST_DIR=	doubly_linked_list
LIB_ADD	+=	-ldlinkedlist
LIBS	+=	DLLIST.lib

LIBFT	=	libft.a
LIBFT_DIR=	libft
LIB_ADD	+=	-lft
LIBS	+=	LIBFT.lib


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
