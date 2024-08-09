/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:45:38 by labdello          #+#    #+#             */
/*   Updated: 2024/08/09 09:39:49 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_open(char *filename, int is_infile)
{
	int	fd;

	if (is_infile)
		fd = open(filename, O_RDONLY, 0777);
	else
		fd = open(filename, O_WRONLY, O_CREAT, O_TRUNC, 0777);
	if (!fd)
		exit(1);
	return (fd);
}

char	*my_getenv(char *name, char **env);

char	*get_path(char *cmd, char **env);
