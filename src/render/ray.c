/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:14:06 by phofer            #+#    #+#             */
/*   Updated: 2026/03/31 13:29:50 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Computes ray direction and delta distances for screen column x.
** camera_x maps [0, WIDTH] to [-1, 1] across the camera plane.
** delta_dist is set to a large value when the ray component is zero
** so that axis is never chosen during DDA stepping.
*/
static void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / WIDTH - 1.0;
	ray->ray_dir_x = game->player.dir_x
		+ game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y
		+ game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->ray_dir_x == 0.0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0.0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

// Sets the step direction and the initial side distances for DDA.
static void	calc_step_side(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

/*
** Steps through the grid one cell at a time along the ray until a wall
** is hit or the map boundary is reached. The boundary guard prevents
** an out-of-bounds read on maps that are not fully enclosed by walls.
*/
static void	perform_dda(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->map_x < 0 || ray->map_y < 0
			|| ray->map_x >= game->map.width
			|| ray->map_y >= game->map.height)
		{
			ray->hit = 1;
			break ;
		}
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
		{
			ray->hit = 1;
			break ;
		}
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}

// Converts perpendicular wall distance to a draw range on screen.
static void	calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = HEIGHT / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = HEIGHT / 2 + ray->line_height / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

// Entry point: runs all four ray stages for screen column x.
void	cast_ray(t_game *game, t_ray *ray, int x)
{
	init_ray(game, ray, x);
	calc_step_side(game, ray);
	perform_dda(game, ray);
	calc_wall_height(ray);
}
