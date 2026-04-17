/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:16:13 by phofer            #+#    #+#             */
/*   Updated: 2026/04/17 14:06:46 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Called every time the mouse moves. Computes the horizontal offset
** from the window centre, converts it to a rotation angle scaled by
** MOUSE_SENSITIVITY, then rotates the player's dir and plane vectors.
** The pointer is warped back to centre after each event so the offset
** never accumulates and the player can look indefinitely left or right.
** Vertical mouse movement is intentionally ignored (no pitch in cub3D).
*/
/**int	mouse_move(int x, int y, t_game *game)
{
	int		center_x;
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	(void)y;
	center_x = WIDTH / 2;
	if (x == center_x)
		return (0);
	angle = (x - center_x) * MOUSE_SENSITIVITY;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = old_dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = old_plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
	mlx_mouse_move(game->mlx, game->win, center_x, HEIGHT / 2);
	return (0);
}
*/
int	mouse_move(int x, int y, t_game *game)
{
	int	center_x;

	(void)y;
	if (!game->mouse_enabled)
		return (0);
	center_x = WIDTH / 2;
	if (!game->mouse_centered)
	{
		game->mouse_centered = 1;
		mlx_mouse_move(game->mlx, game->win, center_x, HEIGHT / 2);
		return (0);
	}
	game->mouse_delta_x = x - center_x;
	mlx_mouse_move(game->mlx, game->win, center_x, HEIGHT / 2);
	return (0);
}
