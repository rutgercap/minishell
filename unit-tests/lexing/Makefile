NAME		:=	lextest

SRCS_DIR	:=	../../srcs
INCL_DIR	:=	../../includes

# Srcs
SRCS		:=	lexing_tester.c \
				$(SRCS_DIR)/lexer/lexer.c \
				$(SRCS_DIR)/lexer/token_list_utils.c \
				$(SRCS_DIR)/lexer/tokenizer.c \
				$(SRCS_DIR)/utils/exit_error.c \
				$(SRCS_DIR)/utils/ft_calloc.c \
				$(SRCS_DIR)/utils/ft_isspace.c \
				$(SRCS_DIR)/utils/ft_strcpy.c \
				$(SRCS_DIR)/utils/ft_strlen.c \
				$(SRCS_DIR)/utils/ft_bzero.c \
				$(SRCS_DIR)/utils/ft_putendl_fd.c \
				$(SRCS_DIR)/utils/ft_putstr_fd.c \
				$(SRCS_DIR)/utils/ft_putchar_fd.c \
				$(SRCS_DIR)/utils/ft_putnbr_fd.c
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
	./$(NAME)
	clean

drun: all
	lldb $(NAME)

clean:
	@rm -rf *.o

fclean:	clean
	@rm -f $(OBJS)

re:	fclean all

.PHONY:	all clean fclean re