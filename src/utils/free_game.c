/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:46:41 by thchau            #+#    #+#             */
/*   Updated: 2026/03/30 20:15:42 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	if (game->map.grid)
		free_lines(game->map.grid, game->map.height);
	i = 0;
	while (i < 4)
	{
		if (game->textures[i])
			free(game->textures[i]);
		i++;
	}
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