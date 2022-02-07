/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_test_cmd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 15:36:15 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/07 13:03:10 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

t_cmd   *make_test_command(t_exec *exec, t_red *input, t_red *output, t_cmd *next)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (exec)
		new->exec = exec;
	if (input)
		new->input = input;
	if (output)
		new->output = output;
	if (next)
		new->next = next;
}

t_red	*make_test_red(t_type type, char *file, t_red *next)
{
	t_red	*new;

	new = ft_calloc(1, sizeof(t_red));
	new->type = type;
	if (file)
		new->file_name = ft_strdup(file);
	if (next)
		new->next = next;
}

t_exec	*make_test_exec(char **arguments)
{
	t_exec	*new;

	new = ft_calloc(1, sizeof(t_exec));
	new->arguments = arguments;
	new->command = arguments[0];
}

char	**make_test_args(int n, char *first, char *second, char *third, char *fourth)
{
	char	*new;

	new = ft_calloc(n + 1, sizeof(char *));
	if (first)
		new[0] = first;
	if (second)
		new[1] = second;
	if (third)
		new[2] = third;
	if (fourth)
		new[3] = fourth;
	return (new);
}

// staat gelijk aan: ls -l
t_cmd	*first_command(void)
{
	t_cmd	*cmd;
	t_exec	*exec;
	char	**args;

	args = make_test_args(2, "ls", "-l", NULL, NULL);
	exec = make_test_exec(args);
	make_test_command(exec, NULL, NULL, NULL);
	return (cmd);
}

// staat gelijk aan: echo test > file1 >> file2 < file3
t_cmd	*second_command(void)
{
	t_cmd	*cmd;
	t_exec	*exec;
	t_red	*output;
	t_red	*input;
	char	**args;

	args = make_test_args(2, "echo", "test", NULL, NULL);
	exec = make_test_exec(args);
	output = make_test_red(RED_OPUT, "file1", NULL);
	output->next = make_test_red(RED_OPUT_A, "file2", NULL);
	input = make_test_red(RED_IPUT, "file3", NULL);
	cmd = make_test_command(exec, input, output, NULL);
	return (cmd);
}

// staat gelijk aan: echo hallo | cat >> file1
// hierbij is dus geen redirect voor de pipe in de struct. 
// die kan toegevoegd worden als dat makkelijker werkt
t_cmd	*third_command(void)
{
	t_cmd	*cmd_1;
	char	**args_1;
	t_exec	*exec_1;
	char	**args_2;
	t_exec	*exec_2;
	t_red	*output_2;

	args_1 = make_test_args(2, "echo", "hallo", NULL, NULL);
	exec_1 = make_test_exec(args_1);
	args_2 = make_test_args(1, "cat", NULL, NULL, NULL);
	exec_2 = make_test_exec(args_2);
	output_2 = make_test_red(RED_OPUT_A, "file1", NULL);
	cmd_1 = make_test_command(exec_1, NULL, NULL, NULL);
	cmd_1->next = make_test_command(exec_2, NULL, output_2, NULL);
	return (cmd_1);
}
