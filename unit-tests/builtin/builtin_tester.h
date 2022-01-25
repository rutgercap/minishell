#ifndef BUILTIN_TESTER_H
# define BUILTIN_TESTER_H

#include <stdio.h>
#include "builtin.h"

void	tester_unset(char **env, char *test);
void	tester_env(char **env);
void	tester_exit(char **env);
void	tester_echo(char **env, char *test);
void	tester_pwd(char **env);
void	tester_export(char **env, char *test);

#endif
