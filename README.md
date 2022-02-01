# Minishell
Rebuilding a simple shell program

## To do

- Badges

#### Required

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


#### Sources

build linux parser:

https://blog.devgenius.io/lets-build-a-linux-shell-part-i-954c95911501

AST example:

https://stackoverflow.com/questions/52666511/create-an-ast-from-bash-in-c/52667521

Redirects:

https://www.gnu.org/software/bash/manual/html_node/Redirections.html

Hilmi tips:

http://www.throwtheswitch.org/unity
https://cs61.seas.harvard.edu/site/2021/Section10/

bash parser:
https://mywiki.wooledge.org/BashParser
