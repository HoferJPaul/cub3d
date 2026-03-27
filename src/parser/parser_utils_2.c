/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 21:15:58 by thchau            #+#    #+#             */
/*   Updated: 2026/03/27 21:13:39 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

/*
** Parse "F 220,100,0"
*/
int	parse_rgb_line(const char *line)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	if (line[0] == 'F' || line[0] == 'C')
		line += 2;
	parts = ft_split(line, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
		return (FAILURE);
	if (!is_number(parts[0]) || !is_number(parts[1]) || !is_number(parts[2]))
		return (FAILURE);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	if (r > 255 || g > 255 || b > 255)
		return (FAILURE);
	free_arr(parts);
	return ((r << 16) | (g << 8) | b);
}

const char	*find_floor_line(char **lines, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		if (ft_strncmp(lines[i], "F ", 2) == 0)
			return (lines[i]);
		i++;
	}
	return (NULL);
}

const char	*find_ceiling_line(char **lines, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		if (ft_strncmp(lines[i], "C ", 2) == 0)
			return (lines[i]);
		i++;
	}
	return (NULL);
}
