NAME		:=	test

SRCS_DIR	:=	../../srcs
INCL_DIR	:=	../../includes

# Srcs
SRCS		:=	builtin_tester.c \
				$(SRCS_DIR)/builtins/built_in.c \
				$(SRCS_DIR)/builtins/mini_echo.c \
				$(SRCS_DIR)/builtins/mini_unset.c \
				$(SRCS_DIR)/utils/ft_split.c \
				$(SRCS_DIR)/utils/ft_strncmp.c \
				$(SRCS_DIR)/utils/ft_strlcpy.c \
				$(SRCS_DIR)/utils/ft_strlen.c \
				$(SRCS_DIR)/utils/ft_putendl_fd.c
OBJS		:=	$(SRCS:.c=.o)

# Config
CC			:=	gcc
FLAGS		:=	-Wall -Wextra -g

# fix relink
all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -I$(INCL_DIR) -o $@

run: all
	./$(NAME) > output
	
auto: all
	./$(NAME) > output
	diff output compare

drun: all
	lldb $(NAME)

clean:
	@rm -rf $(OBJS)

fclean:	clean
	@rm -f $(OBJS)

re:	fclean all

.PHONY:	all clean fclean re