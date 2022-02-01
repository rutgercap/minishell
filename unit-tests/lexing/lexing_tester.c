#include "testing.h"

static void	test(char *line, int mode)
{
	t_token	*tokens;

	tokens = tokenizer(line);
	write_all_tokens(tokens, mode);
	free_tokens(&tokens);
}

int main(void)
{	
	test("ls -l", 0);
	test("hi", 0);
	test("blabla", 0);
	test("sleep 3", 0);
	test("sleep a", 0);
	test("   sleep   ", 0);
	test("sleep 3 | sleep 3", 0);
	test("", 0);
	test(">", 0);
	test(">>", 0);
	test("<", 0);
	test("<<", 0);
	test("||", 0);
	test("|", 0);
	test("echo \"  hi  this is a test\"", 0);
	test("echo \'  hi  this is a test\'", 0);
	test("         ", 0);
	test("      echo \"blabla  ", 0);
	test("      echo   3>1", 0);
}
