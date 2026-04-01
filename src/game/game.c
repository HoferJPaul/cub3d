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

// Zeroes the game struct, runs init stages in order, then enters the loop.
void	start_game(t_game *game, char *map)
{
//	ft_memset(game, 0, sizeof(t_game)); --> game was initualized before
// jumping here. See main funtion 
	init_mlx(game);
	//init_game(game, map); TODO: Parsing .cub, initializing
	init_game_test(game, map); //for testing only
	mlx_loop(game->mlx);
	//game_cleanup(game); TODO:
}
