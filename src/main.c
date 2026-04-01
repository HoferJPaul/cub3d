/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:22:49 by phofer            #+#    #+#             */
/*   Updated: 2026/03/31 15:54:25 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Entry point: validates argument count then launches the game.
int main(int argc, char **argv)
{
	t_game	game;

	initialize(&game);
	if (argc != 2)
	{
		write(2, "Usage: ./cub3D <map.cub>\n", 25);
		return (1);
	}
	start_game(&game, argv[1]);
	cleanup(&game);
	return (0);
}
