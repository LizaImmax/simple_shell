/**
 * get_input - Gets a command from user.
 * @vars: store the command.
 * @ex_retrn: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_input(char *vars, int *ex_retrn)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (vars)
		free(vars);

	read = _getline(&vars, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_input(vars, ex_retrn));
	}

	vars[read - 1] = '\0';
	variable_replacement(&vars, ex_retrn);
	handle_line(&vars, read);

	return (vars);
}

/**
 * querry_input - Check the command in the system.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @ex_retrn: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int querry_input(char **args, char **front, int *ex_retrn)
{
	int retrn, index;

	if (!args[0])
		return (*ex_retrn);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			retrn = run_command(args, front, ex_retrn);
			if (*ex_retrn != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (retrn);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			retrn = run_command(args, front, ex_retrn);
			if (*ex_retrn == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (retrn);
			}
		}
	}
	args = replace_aliases(args);
	retrn = run_command(args, front, ex_retrn);
	return (retrn);
}

/**
 * run_command - executes the command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @ex_retrn: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_command(char **args, char **front, int *ex_retrn)
{
	int retrn, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		retrn = builtin(args + 1, front);
		if (retrn != EXIT)
			*ex_retrn = retrn;
	}
	else
	{
		*ex_retrn = execute(args, front);
		retrn = *ex_retrn;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (retrn);
}

/**
 * handle_args - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int exec_commnad(int *ex_retrn)
{
	int retrn = 0, index;
	char **args, *line = NULL, **front;

	line = get_input(line, ex_retrn);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (retrn);
	if (check_input(args) != 0)
	{
		*ex_retrn = 2;
		free_args(args, args);
		return (*ex_retrn);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			retrn = querry_input(args, front, ex_retrn);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		retrn = querry_input(args, front, ex_retrn);

	free(front);
	return (retrn);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_input(char **args)
{
	size_t i;
	char *curr, *next;

	for (i = 0; args[i]; i++)
	{
		curr = args[i];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (i == 0 || curr[1] == ';')
				return (error_c(&args[i], 2));
			next = args[i + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (error_c(&args[i + 1], 2));
		}
	}
	return (0);
}
