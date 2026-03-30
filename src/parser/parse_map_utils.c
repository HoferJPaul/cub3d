/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:07:19 by thchau            #+#    #+#             */
/*   Updated: 2026/03/30 18:21:12 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

static void	set_player_info(t_game *game, char c, int x, int y)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	if (c == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	if (c == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	if (c == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	if (c == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
}

int	find_player(t_game *game)
{
	int		x;
	int		y;
	int		found;
	char	c;

	y = -1;
	found = 0;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				set_player_info(game, c, x, y);
				found++;
			}
		}
	}
	if (found != 1)
		return (log_err("Map must have exactly one player (N/S/E/W."), FAILURE);
	return (SUCCESS);
}
