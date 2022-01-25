NAME		:=	tester_builtin

GREEN = \033[38;5;2m
NORMAL = \033[38;5;255m
RED = \033[38;5;1m
BLUE = \033[38;5;4m
YELLOW = \033[1;33m

SRCS_DIR	:=	../../srcs
INCL_DIR	:=	../../includes

# Srcs
SRCS		:=	builtin_tester.c \
				tester_unset.c \
				tester_env.c \
				tester_exit.c \
				tester_pwd.c \
				tester_echo.c \
				tester_export.c \
				$(SRCS_DIR)/builtins/built_in.c \
				$(SRCS_DIR)/builtins/mini_echo.c \
				$(SRCS_DIR)/builtins/mini_unset.c \
				$(SRCS_DIR)/builtins/mini_export.c \
				$(SRCS_DIR)/builtins/free_old_env.c \
				$(SRCS_DIR)/utils/ft_split.c \
				$(SRCS_DIR)/utils/ft_strncmp.c \
				$(SRCS_DIR)/utils/ft_strcpy.c \
				$(SRCS_DIR)/utils/ft_strlen.c \
				$(SRCS_DIR)/utils/ft_putendl_fd.c \
				$(SRCS_DIR)/utils/ft_calloc.c \
				$(SRCS_DIR)/utils/ft_putchar_fd.c \
				$(SRCS_DIR)/utils/ft_putstr_fd.c \
				$(SRCS_DIR)/utils/ft_substr.c \
				$(SRCS_DIR)/utils/ft_bzero.c \
				$(SRCS_DIR)/utils/ft_memcpy.c \
				$(SRCS_DIR)/utils/ft_check_malloc.c \
				$(SRCS_DIR)/utils/exit_error.c \



OBJS		:=	$(SRCS:.c=.o)

# Config
CC			:=	gcc
FLAGS		:=	-Wall -Wextra -g

ifdef debug
	FLAGS := -Wall -Wextra -fsanitize=address -g3
else
	FLAGS := -Wall -Werror -Wextra
endif

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