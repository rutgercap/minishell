NAME		:=	minishell

# Directories
INCL_DIR	:=	includes
SRCS_DIR	:=	srcs
OBJDIR		:=	objs
vpath 		%.c $(SRCS_DIR)
vpath 		%.c $(SRCS_DIR)/builtins
vpath		%.c $(SRCS_DIR)/executor
vpath		%.c $(SRCS_DIR)/parser
vpath		%.c $(SRCS_DIR)/utils

# Config
CC			:=	gcc
FLAGS		:=	-Wall -Wextra #-Werror || annoying during development

# Srcs
SRCS		:=	main.c \
				sigactions.c \
				exit_error.c \
				ft_strlen.c \
				ft_bzero.c \
				ft_strcpy.c
OBJS		:=	$(SRCS:.c=.o)


all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(addprefix $(OBJDIR)/, $(OBJS)) $(FLAGS) -o $(NAME)

%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -I$(INCL_DIR) -o $(addprefix $(OBJDIR)/, $@)

run: all
	./$(NAME)

drun: all
	lldb $(NAME)

clean:
	@rm -rf $(OBJDIR)

fclean:		clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re