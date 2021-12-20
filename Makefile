NAME		=	minishell
SRCDIR		=	srcs
SRCS		=	main.c
OBJDIR		=	objs
OBJS		=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CC			=	gcc
FLAGS		=	-Wall -Wextra #-Werror
INCS		=	includes

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(NAME)

$(OBJDIR)/%.o:  $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@ -I$(INCS)

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