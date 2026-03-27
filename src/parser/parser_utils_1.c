/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:32:11 by thchau            #+#    #+#             */
/*   Updated: 2026/03/27 21:10:45 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

/*
** Count lines in file
*/
static int	count_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	return (count);
}

/*
** Remove newline at the end of line
*/
static void	remove_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

/*
** Read file into char **line
*/
char	**read_file_lines(const char *filename, int *line_count)
{
	int		fd;
	int		i;
	char	**lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	*line_count = count_lines(fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = malloc(sizeof(char *) * (*line_count));
	if (!lines)
		return (close(fd), NULL);
	i = -1;
	while (++i < *line_count)
	{
		lines[i] = get_next_line(fd);
		if (!lines[i])
			return (close(fd), NULL);
		remove_newline(lines[i]);
	}
	return (close(fd), lines);
}

void	free_lines(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	free_arr(char **arr)
{
	int	i;
	
	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
