/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/08/14 16:28:40 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		print_error();
		ft_free_tab(cmd_tab);
	}
}

void	open_pipe(char *cmd, char **env, int outfile)
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
		if (outfile == -1)
			dup2(pipe_fd[1], 1);
		else
			dup2(outfile, 1);
		exec(cmd, env);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		waitpid(pid, NULL, 0);
	}
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}

void	pipex(char **args, int infile, int outfile, char **env)
{
	int	i;

	i = 0;
	dup2(infile, 0);
	while (args[i + 2] != NULL)
	{
		open_pipe(args[i], env, -1);
		i++;
	}
	open_pipe(args[i], env, outfile);
}

int	main(int ac, char **av, char **env)
{
	int	infile;
	int	outfile;

	if (ac != 5)
		return (1);
	infile = handle_open(av[1], 1);
	outfile = handle_open(av[ac - 1], 0);
	pipex(av + 2, infile, outfile, env);
	return (0);
}
