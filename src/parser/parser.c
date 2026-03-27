/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 20:00:22 by thchau            #+#    #+#             */
/*   Updated: 2026/03/26 20:31:10 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int	parse_file(t_game *game, const char *filename)
{
	int		line_count;
	char	**lines;

	line_count = 0;
	lines = read_file_lines(filename, &line_count);
	if (!lines)
		return (FAILURE);
	if (parse_textures(game, lines, line_count) != 0)
		return (FAILURE);
	if (parse_colors(game,
			find_floor_line(lines, line_count),
			find_ceiling_line(lines, line_count)) != 0)
		return (FAILURE);
	if (parse_map(game, lines, line_count) != 0)
		return (FAILURE);
	if (validate_map(game) != 0)
		return (FAILURE);
	free_lines(lines, line_count);
	return (SUCCESS);
}
