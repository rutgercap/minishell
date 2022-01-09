# minishell
Rebuilding a simple shell program

### To do

- Finish signals
- lexing
- parsing
- execution of cmds


### Required

GNU readline library is required to run this. Correct path to readline must be included in the makefile.

```console

brew install readline

```

### Exit codes

1: miscellaneous (?)

2: malloc failure


#### Sources

R:
build linux parser:
https://blog.devgenius.io/lets-build-a-linux-shell-part-i-954c95911501
bash prompts:
https://wiki.archlinux.org/title/Bash/Prompt_customization

#### To check

includes/exit.c: header maken voor builtins? alternatief is gewoon stdlib includen.
lexer/tokenizer.c: ft_stchr gebruiken of aparte functies?
