#include "../testing.h"

// $$ $ $ $
// $$$
// echo hi$HOMEhi
// echo hi$HOMEhi$HOME

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
	test("", 0, env);
	test("nothing \"should happen\" here", 0, env);
	test("expand $PAGER", 0, env);
	test("$", 0, env);
	test("$ $ $ $", 0, env);
	test("echo \"hi\"", 0, env);
	test("$PAGER", 0, env);
	test("\'$PAGER\'", 0, env);
	test("$?hi", 0, env);
	test("$?$SHLVL", 0, env);
	test("$?$SHLVLhi", 0, env);
}
