/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:46:41 by thchau            #+#    #+#             */
/*   Updated: 2026/03/31 10:24:02 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_game *game)
{
	int i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->textures[i].img_ptr)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img_ptr);
			game->textures[i].img_ptr = NULL;
		}
		if (game->texture_path[i])
		{
			free(game->texture_path[i]);
			game->texture_path[i] = NULL;
		}
		i++;
	}
}

static void	destroy_img(t_game *game, t_img *img)
{
	if (img->img_ptr)
	{
		mlx_destroy_image(game->mlx, img->img_ptr);
		img->img_ptr = NULL;
	}
}

void	free_game(t_game *game)
{
	destroy_img(game, &game->img);
	destroy_img(game, &game->minimap);
	if (game->map.grid)
		free_lines(game->map.grid, game->map.height);
	free_textures(game);
	if (game->img.img_ptr && game->mlx)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);

	// destroy display (Linux only, safe to ignore on macOS)
	#ifdef __linux__
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	#endif
}