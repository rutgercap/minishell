#include "testing.h"

static void	test(char *line)
{
	t_token	*tokens;

	tokens = tokenizer(line);
	write_all_tokens(tokens);
	free_tokens(&tokens);
}

int main(void)
{	
	test("blabla |");
	test("ls -l");
	test("hi");
	test("sleep 3");
	test("sleep a");
	test("   sleep   ");
	test("sleep 3 | sleep 3");
	test("");
	test(">");
	test(">>");
	test("<");
	test("<<");
	test("||");
	test("|");
	test("echo \"  hi  this is a test\"");
	test("echo \'  hi  this is a test\'");
	test("         ");
	test("      echo \"blabla  ");
	test("      echo   3>1");
}
