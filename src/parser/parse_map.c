/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:04:24 by thchau            #+#    #+#             */
/*   Updated: 2026/04/01 08:27:55 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line || !line[0])
		return (false);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& !ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	find_map_start(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	get_max_width(char **map, int height)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (i < height)
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

/**
 * Pad with spaces if any line has length smaller than map's width
 */
static void	normalize_map(t_game *game)
{
	int		y;
	int		x;
	char	*new_line;

	y = 0;
	while (y < game->map.height)
	{
		new_line = malloc(game->map.width + 1);
		x = 0;
		while (x < game->map.width)
		{
			if (x < (int)ft_strlen(game->map.grid[y]))
				new_line[x] = game->map.grid[y][x];
			else
				new_line[x] = ' ';
			x++;
		}
		new_line[x] = '\0';
		free(game->map.grid[y]);
		game->map.grid[y] = ft_strdup(new_line);
		free(new_line);
		y++;
	}
}

/**
 * parse_map - Parses the map data from input lines
 * @game: Pointer to the game structure to store parsed map data
 * @lines: Array of strings containing the map lines to parse
 * @count: Number of lines in the lines array
 *
 * Description:
 *     Processes the input lines to extract and validate map configuration.
 *     Populates the game structure with parsed map information.
 *
 * Return: 1 on success, -1 on failure
 */
int	parse_map(t_game *game, char **lines, int count)
{
	int	start;
	int	i;
	int	height;

	start = find_map_start(lines, count);
	if (start == -1)
		return (log_err("There is no map in the file."), FAILURE);
	height = count - start;
	game->map.grid = malloc(sizeof(char *) * (height + 1));
	if (!game->map.grid)
		return (log_err("allocate map.grid failed."), FAILURE);
	i = 0;
	while (i < height)
	{
		if (!is_map_line(lines[start + i]))
			return (log_err("Map must be the last one."), FAILURE);
		game->map.grid[i] = ft_strdup(lines[start + i]);
	}
	game->map.grid[i] = NULL;
	game->map.height = height;
	game->map.width = get_max_width(game->map.grid, height);
	normalize_map(game);
	return (find_player(game));
}
