/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:15:40 by phofer            #+#    #+#             */
/*   Updated: 2026/04/07 14:54:03 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

static int	get_tex_x(t_game *game, t_ray *ray, t_img *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->step_x > 0)
		|| (ray->side == 1 && ray->step_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_column(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;
	int		tex_x;
	double	tex_step;
	double	tex_pos;

	tex = &game->textures[get_tex_index(ray)];
	tex_x = get_tex_x(game, ray, tex);
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
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}
