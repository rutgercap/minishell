vpath %.c $(SRCS_DIR)
vpath %.h $(INCL_DIR)

NAME		=	minishell
SRCS_DIR	=	srcs
SRCS		=	main.c \
				utils/exit_error.c
OBJDIR		=	objs
OBJS		=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CC			=	gcc
FLAGS		=	-Wall -Wextra #-Werror # weg gehaald omdat het irritant is tijdens development
INCL_DIR	=	includes

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(NAME)

$(OBJDIR)/%.o:  $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@ -I$(INCL_DIR)

run: all
	./$(NAME)

drun: all
	lldb $(NAME)

clean:
	@rm -rf $(OBJDIR)

fclean:		clean
	@rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re