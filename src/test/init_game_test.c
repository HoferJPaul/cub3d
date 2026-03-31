/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:34:25 by thchau            #+#    #+#             */
/*   Updated: 2026/03/31 11:29:38 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_test(t_game *game, char *filename)
{
	if (parse_file(game, filename) == FAILURE)
	{
		log_err("Error happened.");
		free_game(game);
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
}
