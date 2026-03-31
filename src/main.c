/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:59:01 by thchau            #+#    #+#             */
/*   Updated: 2026/03/31 11:25:22 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int main(int argc, char **argv)
{
	t_game game;
	initialize(&game);
	if (argc != 2)
	{
		printf("Usage: ./cub3d map.cub\n");
		return (1);
	}
	init_game_test(&game, argv[1]);
	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	free_game(&game);
    return (0);
}
