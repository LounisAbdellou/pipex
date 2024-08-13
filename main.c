/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/08/13 17:06:32 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(void)
{
	static int	has_error;

	if (has_error != 1)
	{
		perror("pipex");
		has_error = 1;
	}
}

void	exec(char *cmd, char **env)
{
	char		**cmd_tab;
	char		*cmd_path;

	cmd_tab = ft_split(cmd, ' ');
	if (!cmd_tab)
		exit(0);
	cmd_path = get_path(cmd_tab[0], env);
	if (execve(cmd_path, cmd_tab, env) == -1)
	{
		// ft_putstr_fd("pipex: command not found :", 1);
		// ft_putendl_fd(cmd_tab[0], 1);
		print_error();
		ft_free_tab(cmd_tab);
		// exit(0);
	}
}

void	open_pipe(char *cmd, char **env)
{
	int	pid;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		exec(cmd, env);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
	}
}

void	pipex(char **args, int infile, int outfile, char **env)
{
	int	i;

	i = 0;
	dup2(infile, 0);
	while (args[i + 2] != NULL)
	{
		open_pipe(args[i], env);
		i++;
	}
	dup2(outfile, 1);
	exec(args[i], env);
}

int	main(int ac, char **av, char **env)
{
	int	infile;
	int	outfile;

	if (ac < 5)
		return (1);
	infile = handle_open(av[1], 1);
	outfile = handle_open(av[ac - 1], 0);
	pipex(av + 2, infile, outfile, env);
	return (0);
}
