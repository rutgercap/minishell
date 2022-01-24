NAME		:=	minishell

# Readline -- adjust this for your machine
RL_LIB		:=	-L/Users/rcappend/Documents/homebrew/opt/readline/lib
RL_INC		:=	-I/Users/rcappend/Documents/homebrew/opt/readline/include

# Directories
INCL_DIR	:=	includes
SRCS_DIR	:=	srcs
OBJ_DIR		:=	objs
vpath 		%.c $(SRCS_DIR)
vpath 		%.c $(SRCS_DIR)/builtins
vpath		%.c $(SRCS_DIR)/executor
vpath		%.c $(SRCS_DIR)/parser
vpath		%.c $(SRCS_DIR)/utils
vpath		%.c $(SRCS_DIR)/tokenizer

# Srcs
SRCS		:=	main.c \
				signals.c \
				exit_error.c \
				tokenizer.c \
				process_char.c \
				process_char_utils.c \
				mini_exit.c \
				ft_strlen.c \
				ft_bzero.c \
				ft_strjoin.c \
				ft_memcpy.c \
				ft_strdup.c \
				ft_strcpy.c \
				ft_putendl_fd.c \
				ft_putstr_fd.c \
				ft_putchar_fd.c \
				ft_strncmp.c \
				ft_isspace.c \
				ft_strtrim.c \
				ft_strchr.c \
				ft_substr.c \
				ft_strdup.c \
				ft_calloc.c
OBJS		:=	$(SRCS:.c=.o)

# Config
CC			:=	gcc
FLAGS		:=	-Wall -Wextra -g #-Werror || annoying during development
LIBS		:=	-lreadline -lhistory

# fix relink
all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(addprefix $(OBJ_DIR)/, $(OBJS)) $(FLAGS) $(LIBS) $(RL_LIB) -o $(NAME)

%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -I$(INCL_DIR) $(RL_INC) -o $(addprefix $(OBJ_DIR)/, $@)

run: all
	./$(NAME)

drun: all
	lldb $(NAME)

lextest:
	make auto -C unit-tests/lexing
	make clean -C unit-tests/lexing

expandtest:
	make auto -C unit-tests/expander
	make clean -C unit-tests/expander

dtest:
	make drun -C unit-tests/expander
	make clean -C unit-tests/expander

clean:
	@rm -rf $(OBJ_DIR)
	make clean -C unit-tests/expander
	make clean -C unit-tests/lexing

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re