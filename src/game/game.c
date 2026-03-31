/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:39:57 by phofer            #+#    #+#             */
/*   Updated: 2026/03/31 14:08:19 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_game(t_game *game, char *map_path)
{
	if (parse_file(game, map_path) == FAILURE)
	{
		log_err("Error happened.");
		cleanup(game);
		exit(EXIT_FAILURE);
	}
	printf("floor color: %i\n", game->floor_color);
	printf("ceiling color: %i\n", game->ceiling_color);
	printf("NO: %s\n", game->texture_path[NORTH]);
	printf("SO: %s\n", game->texture_path[SOUTH]);
	printf("EA: %s\n", game->texture_path[EAST]);
	printf("WE: %s\n", game->texture_path[WEST]);
	for (int i = 0; i < game->map.height; i++)
        printf("%s\n", game->map.grid[i]);
	load_textures(game);
}

void	start_game(t_game *game, char *map)
{
	initialize(game);
	init_mlx(game);
	init_game(game, map);
	//init_game_test(game, map); //for testing only
	mlx_loop(game->mlx);
	cleanup(game);
}
