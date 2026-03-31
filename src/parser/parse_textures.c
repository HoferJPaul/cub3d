/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 10:55:52 by thchau            #+#    #+#             */
/*   Updated: 2026/03/31 11:13:51 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

static int	set_texture_path(char **field, char *val, const char *dir)
{
	char	*msg;

	if (!val || val[0] == '\0')
	{
		free(val);
		msg = ft_strjoin(dir, " - Empty texture path.");
		if (!msg)
			return (log_err("Failed to join 2 strings."), FAILURE);
		log_err(msg);
		return (free(msg), FAILURE);
	}
	if (*field)
	{
		free(val);
		msg = ft_strjoin(dir, " - Duplicate texture.");
		if (!msg)
			return (log_err("Failed to join 2 strings."), FAILURE);
		log_err(msg);
		return (free(msg), FAILURE);
	}
	*field = val;
	return (SUCCESS);
}

static int	set_all_textures(t_game *game, char *line, char *val)
{
	char	*path;

	path = ft_strdup(val);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (set_texture_path(&game->texture_path[NORTH], path, "NO"));
	if (ft_strncmp(line, "SO", 2) == 0)
		return (set_texture_path(&game->texture_path[SOUTH], path, "SO"));
	if (ft_strncmp(line, "WE", 2) == 0)
		return (set_texture_path(&game->texture_path[WEST], path, "WE"));
	if (ft_strncmp(line, "EA", 2) == 0)
		return (set_texture_path(&game->texture_path[EAST], path, "EA"));
	return (SUCCESS);
}

static int	parse_texture_line(t_game *game, char *line)
{
	char	*ptr;
	char	*start;

	while (ft_isspace(*line))
		line++;
	ptr = line;
	if (ft_strncmp(ptr, "NO", 2) == 0 || ft_strncmp(ptr, "SO", 2) == 0
		|| ft_strncmp(ptr, "WE", 2) == 0 || ft_strncmp(ptr, "EA", 2) == 0)
		ptr += 2;
	else
		return (SUCCESS);
	if (*ptr != ' ')
		return (log_err("Invalid texture format"), FAILURE);
	while (*ptr == ' ')
		ptr++;
	start = ptr;
	while (*ptr && *ptr != ' ')
		ptr++;
	if (*ptr != '\0')
		return (log_err("Texture has too many arguments"), FAILURE);
	return (set_all_textures(game, line, start));
}

/**
 * parse_textures - Parses texture configuration from input lines
 * @game: Pointer to the game structure to store parsed texture data
 * @lines: Array of strings containing configuration lines
 * @count: Number of lines in the lines array
 *
 * Description:
 * Parses texture paths and configuration from the provided lines array
 * and populates the game structure with the extracted texture information.
 *
 * Return: 1 on success, -1 on failure
 */
int	parse_textures(t_game *game, char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (is_map_line(lines[i]))
			break ;
		if (parse_texture_line(game, lines[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
