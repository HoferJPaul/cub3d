/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:15:40 by phofer            #+#    #+#             */
/*   Updated: 2026/03/30 19:11:51 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Selects the correct texture index based on which face of a wall was hit.
** side == 0 means the ray hit an X-aligned wall face (East or West).
** side == 1 means the ray hit a Y-aligned wall face (North or South).
** step tells us which direction the ray was travelling to determine
** which of the two possible faces on that axis was actually hit.
*/
static int	get_tex_index(t_ray *ray)
{
	if (ray->side == 0 && ray->step_x > 0)
		return (TEX_EA);
	if (ray->side == 0 && ray->step_x < 0)
		return (TEX_WE);
	if (ray->side == 1 && ray->step_y > 0)
		return (TEX_SO);
	return (TEX_NO);
}

/*
** Samples one pixel from a texture.
** tex_x is the horizontal position on the texture (which column).
** tex_y is the vertical position on the texture (which row).
** Uses the same addr + line_len + bpp formula as put_pixel, but reads
** instead of writes, and applies a darkening shift on Y-axis wall hits
** to simulate a simple directional light without a real light model.
*/
static int	get_tex_color(t_img *tex, int tex_x, int tex_y, int side)
{
	char	*src;
	int		color;

	src = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	color = *(unsigned int *)src;
	if (side == 1)
		color = COLOR_DARK(color);
	return (color);
}

/*
** Draws one vertical wall slice for screen column x.
**
** wall_x is where exactly on the wall the ray hit, as a value
** between 0.0 and 1.0. Multiplying by the texture width gives
** the correct texture column to sample.
**
** tex_step is how many texture rows to advance per screen pixel.
** tex_pos tracks our current position in the texture as we step
** down the column, accumulating fractional rows.
*/
static void	draw_column(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;
	double	wall_x;
	int		tex_x;
	double	tex_step;
	double	tex_pos;

	tex = &game->textures[get_tex_index(ray)];
	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->step_x > 0)
		|| (ray->side == 1 && ray->step_y < 0))
		tex_x = tex->width - tex_x - 1;
	tex_step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* tex_step;
	while (ray->draw_start <= ray->draw_end)
	{
		put_pixel(&game->img, x, ray->draw_start,
			get_tex_color(tex, tex_x, (int)tex_pos & (tex->height - 1),
				ray->side));
		tex_pos += tex_step;
		ray->draw_start++;
	}
}

/*
** Main render loop called once per frame by mlx_loop_hook.
** Processes held keys, redraws the ceiling/floor background,
** then casts one ray per screen column and draws the resulting
** wall slice before pushing the completed image to the window.
*/
int	render(t_game *game)
{
	t_ray	ray;
	int		x;

	handle_movement(game);
	draw_background(game);
	x = 0;
	while (x < WIDTH)
	{
		cast_ray(game, &ray, x);
		draw_column(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}
