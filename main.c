/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/08/09 09:39:41 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env);

void	open_pipe(char *cmd, char **env);

void	pipex(char **args, int infile, int outfile, char **env)
{
	int	i;

	i = 0;
	while (args[i + 1] != NULL)
	{
		i++;
	}
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
	(void)av;
	return (0);
}
