/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:59:01 by thchau            #+#    #+#             */
/*   Updated: 2026/03/30 20:10:49 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "cub3d.h"
#include "parser.h"

int main(int argc, char **argv)
{
	t_game game;

	initialize(&game);

	if (argc != 2)
	{
		printf("Usage: ./cub3d map.cub\n");
		return 1;
	}
	char *filename = argv[1];
	int line_count;
	char **lines = read_file_lines(filename, &line_count);
	if (!lines)
		return (1);
	parse_file(&game, argv[1]);
	printf("floor color: %i\n", game.floor_color);
	printf("ceiling color: %i\n", game.ceiling_color);
	printf("NO: %s\n", game.textures[NORTH]);
	printf("SO: %s\n", game.textures[SOUTH]);
	printf("EA: %s\n", game.textures[EAST]);
	printf("WE: %s\n", game.textures[WEST]);

	for (int i = 0; i < game.map.height; i++)
        printf("%s\n", game.map.grid[i]);
	mlx_hook(game.win, 2, 1L << 0, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	free_game(&game);
    return 0;
}
