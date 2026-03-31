/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:46:41 by thchau            #+#    #+#             */
/*   Updated: 2026/03/31 14:38:53 by thchau           ###   ########.fr       */
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

/**
 * @brief Frees all dynamically allocated memory associated with the game structure.
 * 
 * This function deallocates all resources held by the game object, including
 * textures, maps, and other game-related data structures. It should be called
 * before program termination to prevent memory leaks.
 * 
 * @param game Pointer to the t_game structure to be freed. If NULL, the function
 *             should handle it gracefully without causing undefined behavior.
 * 
 * @return void
 * 
 * @note This function assumes that all members of the t_game structure have been
 *       properly initialized before being freed.
 */
void	cleanup(t_game *game)
{
	destroy_img(game, &game->img);
	destroy_img(game, &game->minimap);
	if (game->map.grid)
		free_arr(game->map.grid);
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