/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:32:11 by thchau            #+#    #+#             */
/*   Updated: 2026/03/30 18:17:12 by thchau           ###   ########.fr       */
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
/**
 * read_file_lines - Reads all lines from a file into a dynamical array
 * @filename: Path to the file to read
 * @line_count: where the number of lines read will be stored
 *
 * Description:
 * Opens and reads the specified file line by line, storing each line in a
 * dynamically allocated string array. The total number of lines read is stored
 * in the integer pointed to by line_count.
 *
 * Return: A pointer to a dynamically allocated array of strings (char **),
 *         where each string represents a line from the file.
 * 		Returns NULL on error (file not found, memory allocation failure, etc.).
 *         The caller is responsible for freeing the allocated memory.
 *
 * Note: Each line string should have trailing newline characters handled
 *       appropriately. The array should be terminated with a NULL pointer.
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
