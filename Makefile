NAME		:=	minishell

# Readline -- adjust this for your machine
RL_LIB		:=	-L/opt/homebrew/opt/readline/lib
RL_INC		:=	-I/opt/homebrew/opt/readline/include

# Directories
INCL_DIR	:=	includes
SRCS_DIR	:=	srcs
OBJ_DIR		:=	objs
VPATH 		:=	$(subst $(space),:,$(shell find srcs -type d))

# Srcs
SRCS		:=	main.c \
				signals.c \
				exit_error.c \
				tokenizer.c \
				token_utils.c \
				expander.c \
				cmd_utils.c \
				parser.c \
				redirect_utils.c \
				process_char.c \
				process_char_utils.c \
				mini_exit.c \
				ft_check_malloc.c \
				ft_strlcat.c \
				ft_strlcpy.c \
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
				ft_itoa.c \
				ft_abs.c \
				ft_calloc.c
OBJS		:=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Config
CC			:=	gcc
FLAGS		:=	-Wall -Wextra -g #-Werror || annoying during development
LIBS		:=	-lreadline -lhistory

all:		$(NAME)

$(NAME):	$(OBJS)
	@$(CC) $(OBJS) $(FLAGS) $(LIBS) $(RL_LIB) -o $(NAME)
	@echo success!

$(OBJ_DIR)/%.o: $(notdir %.c)
	@mkdir -p $(OBJ_DIR)
	@echo "compiling $(notdir $(basename $@))"
	@$(CC) $(FLAGS) -c $< -I$(INCL_DIR) $(RL_INC) -o $@

run: all
	./$(NAME)

drun: all
	lldb $(NAME)

echo:
	@echo $(OBJS)

clean:
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re