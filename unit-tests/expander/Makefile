NAME		:=	expandtester

SRCS_DIR	:=	../../srcs
INCL_DIR	:=	../../includes

# Srcs
SRCS		:=	expand.c \
				../token_testing.c \
				$(SRCS_DIR)/tokenizer/tokenizer.c \
				$(SRCS_DIR)/tokenizer/process_char.c \
				$(SRCS_DIR)/tokenizer/process_char_utils.c \
				$(SRCS_DIR)/expander/expander.c \
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
				$(SRCS_DIR)/utils/ft_strjoin.c \
				$(SRCS_DIR)/utils/ft_strncmp.c \
				$(SRCS_DIR)/utils/ft_strdup.c \
				$(SRCS_DIR)/utils/ft_itoa.c \
				$(SRCS_DIR)/utils/ft_abs.c \
				$(SRCS_DIR)/utils/ft_putnbr_fd.c
OBJS		:=	$(SRCS:.c=.o)

OUTPUT		:=	output
COMPARE		:=	compare

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
	./$(NAME) > $(OUTPUT)
	
auto: all
	./$(NAME) > $(OUTPUT)
	diff $(OUTPUT) $(COMPARE)

drun: all
	lldb $(NAME)

clean:
	@rm -rf $(OBJS)

fclean:	clean
	@rm -f $(OBJS)

re:	fclean all

.PHONY:	all clean fclean re