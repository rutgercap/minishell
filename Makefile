NAME		:=	minishell

# Readline -- might be different on your machine
RL_DIR		:=	/usr/local/opt/readline/lib

# Directories
INCL_DIR	:=	includes
SRCS_DIR	:=	srcs
OBJ_DIR		:=	objs
vpath 		%.c $(SRCS_DIR)
vpath 		%.c $(SRCS_DIR)/builtins
vpath		%.c $(SRCS_DIR)/executor
vpath		%.c $(SRCS_DIR)/parser
vpath		%.c $(SRCS_DIR)/utils
vpath		%.c $(SRCS_DIR)/lexer


# Srcs
SRCS		:=	main.c \
				signals.c \
				exit_error.c \
				mini_exit.c \
				ft_strlen.c \
				ft_bzero.c \
				ft_strcpy.c \
				ft_putendl_fd.c \
				ft_putstr_fd.c \
				ft_putchar_fd.c \
				ft_strncmp.c \
				ft_isspace.c \
				lexer.c \
				tokenizer.c \
				token_list_utils.c \
				ft_calloc.c
OBJS		:=	$(SRCS:.c=.o)

# Config
CC			:=	gcc
FLAGS		:=	-Wall -Wextra -g #-Werror || annoying during development
LIBS		:=	-L$(RL_DIR) -lreadline -lhistory

# fix relink
all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(addprefix $(OBJ_DIR)/, $(OBJS)) $(FLAGS) $(LIBS) -o $(NAME)

%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -I$(INCL_DIR) -o $(addprefix $(OBJ_DIR)/, $@)

run: all
	./$(NAME)

drun: all
	lldb $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re