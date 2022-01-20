# Minishell
Rebuilding the basics of Bash

## Functionality

- Working history
- Launches executables based on PATH variable or based on relative or absolute path
- Bultins:
  - echo
    - with option -n
  - cd
    - absolute or relative
  - pwd
  - export
  - env
  - exit
- Support for single and double quote strings
- Basic redirections through: '>', '<', '<<' and '>>'.
- Pipes
- Environment variables (including $?)
- Ctrl-C, Ctrl-D and Ctrl-\

## To run

**Readline library is required (see below for how-to)**

```console

make run

```

#### Readline

GNU readline library is required to run this. Correct path to readline must be included in the makefile.

*brew installation:*

```console

brew install readline

```

Then run

```console

brew info readline

```
![compiler path](https://user-images.githubusercontent.com/2053650/150352713-fc5d9da7-046f-46dc-93ff-593e330235fc.png "Compiler path")

Add these to the makefile

![Adjust this](https://user-images.githubusercontent.com/2053650/150352709-ebf59ce0-e609-44da-9351-1c9ffdd1b445.png "Adjust this in makefile")

### Learning goals

- Intrinsics of bash
- Shell environment variables
- Forking in C programs
- Writing scalable code
- Teamwork
- Extensive knowledge of processes and file descriptors

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

