/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:22:49 by phofer            #+#    #+#             */
/*   Updated: 2026/04/01 13:22:39 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	ft_check_extension(const char *filename, const char *ext)
{
	int	flen;
	int	elen;

	if (!filename || !ext)
		return (0);
	flen = ft_strlen(filename);
	elen = ft_strlen(ext);
	if (flen <= elen)
		return (0);
	return (ft_strncmp(filename + flen - elen, ext, elen) == 0);
}

// Entry point: validates argument count then launches the game.
int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Usage: ./cub3D <map.cub>\n", 25);
		return (1);
	}
	if (!ft_check_extension(argv[1], ".cub"))
	{
		write(2, "File must have .cub extension\n", 30);
		return (1);
	}
	start_game(&game, argv[1]);
	return (0);
}
