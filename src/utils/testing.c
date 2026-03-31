/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:31:06 by phofer            #+#    #+#             */
/*   Updated: 2026/03/31 15:54:25 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Fills one texture with a solid color for testing purposes.
** mlx_new_image allocates a blank buffer, then we walk every
** pixel and write the given color into it directly.
*/
static void	fill_texture(t_game *game, int index, int color)
{
	t_img	*tex;
	int		x;
	int		y;

	tex = &game->textures[index];
	tex->img_ptr = mlx_new_image(game->mlx, 64, 64);
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
	tex->width = 64;
	tex->height = 64;
	y = 0;
	while (y < 64)
	{
		x = 0;
		while (x < 64)
			put_pixel(tex, x++, y, color);
		y++;
	}
}

/*
** TODO: parse the .cub file, validate config and map,
** set up the player start position and all runtime defaults.
*/
void	init_game_test(t_game *game, char *map_path)
{
	static char	*grid[] = {
		"111111111",
		"100000001",
		"100000001",
		"100000001",
		"100000001",
		"111111111",
		NULL
	};

	(void)map_path;
	game->map.grid = grid;
	game->map.width = 9;
	game->map.height = 6;
	game->player.x = 4.5;
	game->player.y = 3.0;
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->ceiling_color = SKY_BLUE;
	game->floor_color = DIRT_BROWN;
	fill_texture(game, TEX_NO, RED);
	fill_texture(game, TEX_SO, GREEN);
	fill_texture(game, TEX_WE, BLUE);
	fill_texture(game, TEX_EA, YELLOW);
}
