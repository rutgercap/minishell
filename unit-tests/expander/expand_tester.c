#include "../testing.h"

static void	test(char *line, int mode, char **env)
{
	t_token	*tokens;

	tokens = tokenizer(line);
	expander(tokens, env, 42);
	write_all_tokens(tokens, mode);
	free_tokens(&tokens);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	// test("", 0, env);
	// test("nothing \"should happen\" here", 0, env);
	// test("expand $USER", 0, env);
	test("HOME=$HOME:hallo", 0, env);	// these three should append hallo to $HOME
	test("HOME='$HOME'hallo", 0, env);	// these three should append hallo to $HOME
	test("HOME=$HOME/hallo", 0, env);
	test("HOME=$HOME%hallo", 0, env);
	test("HOME=$HOME|hallo", 0, env);	// error, hello not found
	test("HOME=$HOME'hallo", 0, env);	// error, searching for second '
	test("HOME=$HOME>hallo", 0, env);
	test("HOME=$HOME<hallo", 0, env);
	// test("$", 0, env);
	// test("$ $ $ $", 0, env);
	// test("echo \"hi\"", 0, env);
	// test("$USER", 0, env);
	// test("\'$USER\'", 0, env);
	// test("$?hi", 0, env);
	// test("$?$USER", 0, env);
	// test("$?$USERhi", 0, env);
	// test("$?$USER$?", 0, env);
}
