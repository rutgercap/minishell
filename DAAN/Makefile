NAME		:=	lextest

SRCS_DIR	:=	../srcs
INCL_DIR	:=	../includes

# Srcs
SRCS		:=	tester.c \
				token_tester.c \
				lexing.c \
				lexing_utils.c \
				$(SRCS_DIR)/utils/exit_error.c \
				$(SRCS_DIR)/utils/ft_calloc.c \
				$(SRCS_DIR)/utils/ft_isspace.c \
				$(SRCS_DIR)/utils/ft_strcpy.c \
				$(SRCS_DIR)/utils/ft_strlen.c \
				$(SRCS_DIR)/utils/ft_bzero.c \
				$(SRCS_DIR)/utils/ft_putendl_fd.c \
				$(SRCS_DIR)/utils/ft_putstr_fd.c \
				$(SRCS_DIR)/utils/ft_putchar_fd.c \
				$(SRCS_DIR)/utils/ft_strtrim.c \
				$(SRCS_DIR)/utils/ft_strchr.c \
				$(SRCS_DIR)/utils/ft_substr.c \
				$(SRCS_DIR)/utils/ft_memcpy.c \
				$(SRCS_DIR)/utils/ft_putnbr_fd.c \
				$(SRCS_DIR)/utils/ft_check_malloc.c \
				$(SRCS_DIR)/utils/ft_strdup.c
OBJS		:=	$(SRCS:.c=.o)

# Config
CC			:=	gcc
ifdef debug
	FLAGS := -Wall -Wextra -fsanitize=address -g
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
	./$(NAME)

drun: all
	lldb $(NAME)

clean:
	@rm -rf $(OBJS)

fclean:	clean
	@rm -f $(OBJS)
	@rm -f $(OUTPUT)

re:	fclean all

.PHONY:	all clean fclean re