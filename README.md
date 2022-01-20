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

666: syntax error 


#### Sources

build linux parser:
https://blog.devgenius.io/lets-build-a-linux-shell-part-i-954c95911501

bash prompts:
https://wiki.archlinux.org/title/Bash/Prompt_customization

AST example:
https://stackoverflow.com/questions/52666511/create-an-ast-from-bash-in-c/52667521

Redirects:
https://www.gnu.org/software/bash/manual/html_node/Redirections.html

Hilmi tips:
http://www.throwtheswitch.org/unity
https://cs61.seas.harvard.edu/site/2021/Section10/

#### To check

includes/exit.c: header maken voor builtins? alternatief is gewoon stdlib includen.
lexer/tokenizer.c: ft_stchr gebruiken of aparte functies?

