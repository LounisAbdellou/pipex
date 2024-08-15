/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:05:57 by labdello          #+#    #+#             */
/*   Updated: 2024/08/15 18:05:02 by labdello         ###   ########.fr       */
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

int	handle_open(char *filename, int is_infile)
{
	int	fd;

	if (is_infile)
		fd = open(filename, O_RDONLY, 0777);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		print_error();
	return (fd);
}

char	*get_env(char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0' && env[i][j] != '=')
			j++;
		str = ft_strndup(env[i], j);
		if (ft_strcmp(str, "PATH") == 0)
		{
			free(str);
			return (env[i] + j + 1);
		}
		free(str);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**paths;
	char	*path;
	char	**cmd_tab;

	i = 0;
	paths = ft_split(get_env(env), ':');
	cmd_tab = ft_split(cmd, ' ');
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(path, cmd_tab[0]);
		free(path);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(cmd_tab);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_free_tab(paths);
	ft_free_tab(cmd_tab);
	return (cmd);
}
