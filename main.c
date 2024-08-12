/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/08/12 17:41:18 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{

}

void	open_pipe(char *cmd, char **env);
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
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid);
}

void	pipex(char **args, int infile, int outfile, char **env)
{
	int	i;

	i = 0;
	dup2(infile, 0);
	while (args[i + 1] != NULL)
	{
		open_pipe(args[i], env);
		i++;
	}
	dup2(outfile, 1);
}

int	main(int ac, char **av, char **env)
{
	int	infile;
	int	outfile;

	if (ac < 5)
		return (1);
	infile = handle_open(av[1], 0);
	outfile = handle_open(av[ac - 1], 1);
	pipex(av + 2, infile, outfile, env);
	return (0);
}
