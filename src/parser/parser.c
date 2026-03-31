/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:00:22 by thchau            #+#    #+#             */
/*   Updated: 2026/03/31 13:54:05 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

/**
 * @brief Parses a configuration file and initializes game settings
 * @param game Pointer to the game structure to be populated with parsed data
 * @param filename Path to the configuration file to parse
 * @return int Returns 1 on successful parsing, -1 on failure
 * 
 * @details This function reads and validates the configuration file specified
 * by filename and populates the game structure with the parsed settings.
 * The function handles file validation, format checking, and error reporting.
 */
int	parse_file(t_game *game, const char *filename)
{
	int		line_count;
	char	**lines;

	line_count = 0;
	lines = read_file_lines(filename, &line_count);
	if (!lines)
		return (FAILURE);
	if (parse_textures(game, lines, line_count) != SUCCESS)
		return (free_arr(lines), FAILURE);
	if (parse_colors(game, lines, line_count) != SUCCESS)
		return (free_arr(lines), FAILURE);
	if (validate_elements(game) != SUCCESS)
		return (free_arr(lines), FAILURE);
	if (parse_map(game, lines, line_count) != SUCCESS)
		return (free_arr(lines), FAILURE);
	if (validate_map(game) != SUCCESS)
		return (free_arr(lines), FAILURE);
	free_arr(lines);
	return (SUCCESS);
}
