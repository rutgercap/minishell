NAME				:=	tester

# Minishell directories
SRCS_P				:=	../srcs/
MINI_SRCS			:=	$(SRCS_P)$(wildcard *.c) $(SRCS_P)$(wildcard */*.c)

# Testing directories
PATHB 				:=	build/
PATHD				:=	build/depends/
PATHO				:=	build/objs/
PATHR				:=	build/results/
PATHT				:=	./
UNITY_P 			:=	unity/src/
SRC_TESTS			:=	*.c

# Configuration
TARGET_EXTENSION	:=	.out
COMPILE				:=	gcc -c
LINK				:=	gcc
DEPEND				:=	gcc -MM -MG -MF
INCLUDES			:=	-I. -I$(PATHU) -I$(PATHS)
CFLAGS				:=	-Wall -Wextra -fsanitize=address -g

all:		$(NAME)
$(NAME):	$(OBJS)

test: $(BUILD_PATHS) $(RESULTS)
    @echo "ignores:"
    @echo `grep -s IGNORE $(PATHR)*.txt`
    @echo "-----------------------\nFAILURES:\n-----------------------"
    @echo `grep -s FAIL $(PATHR)*.txt`
    @echo "\nDONE"

RESULTS = $(patsubst $(PATHT)Test%.c,$(PATHR)Test%.txt,$(SRC_T))

$(PATHR)%.txt: $(PATHB)%.$(TARGET_EXTENSION)
    -./$< > $@ 2>&1

$(PATHB)Test%.$(TARGET_EXTENSION): $(PATHO)Test%.o $(PATHO)%.o $(PATHO)unity.o $(PATHD)Test%.d
    $(LINK) -o $@ $^

$(PATHO)%.o:: $(PATHT)%.c
    $(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c
    $(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
    $(COMPILE) $(CFLAGS) $< -o $@ 

$(PATHD)%.d:: $(PATHT)%.c
    $(DEPEND) $@ $<

$(PATHB):
    $(MKDIR) $(PATHB)

$(PATHD):
    $(MKDIR) $(PATHD)

$(PATHO):
    $(MKDIR) $(PATHO)

$(PATHR):
    $(MKDIR) $(PATHR)

.PHONY: clean
.PHONY: test