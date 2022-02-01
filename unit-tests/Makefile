NAME		:=	tester

# mini srcs /dirs
INCL_DIR	:=	../includes
SRCS_DIR	:=	../srcs
OBJ_DIR		:=	../objs
VPATH		:=	$(subst $(space),:,$(shell find $(SRCS_DIR) -type d))

# unity srcs / dirs
UNITY_DIR	:=	unity
UNITY_SRC	:=	$(UNITY_DIR)/src/unity.c
UNITY_OBJ	:=	$(addprefix $(OBJ_DIR)/, $(notdir $(UNITY_SRC:.c=.o)))

# testing srcs / dirs
RES_DIR		:=	results
TEST_SRCS	:=	$(wildcard *.c)
ALL_SRCS	:=	$(TEST_SRCS) $(SRCS)
OBJS		:=	$(addprefix $(OBJ_DIR)/, $(ALL_SRCS:.c=.o))

# Config
FLAGS		:=	-Wall -Wextra -fsanitize=address -g
LIBS		:=	-lreadline -lhistory

all:	$(NAME)
$(NAME):	$(UNITY_OBJ) $(OBJS)
	@$(CC) $(OBJS) $(UNITY_OBJ) $(FLAGS) $(LIBS) $(RL_LIB) -o $(NAME)
	@echo compiled successfully!

$(UNITY_OBJ):
	@$(CC) $(FLAGS) -c $(UNITY_SRC) -I$(INCL_DIR) -I$(UNITY_DIR)/src $(RL_INC) -o $@

$(OBJ_DIR)/%.o: $(notdir %.c)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -I$(INCL_DIR) -I$(UNITY_DIR)/src $(RL_INC) -o $@

run: all $(RES_DIR)
	@./$(NAME) 2>&1 > $(RES_DIR)/results.txt

echo:
	@echo $(OBJS)

$(RES_DIR):
	@mkdir -p $(RES_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(RES_DIR)

fclean: clean
	@rm -f $(NAME)