/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 20:58:21 by thchau            #+#    #+#             */
/*   Updated: 2026/03/30 12:53:18 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <mlx.h>

# define SUCCESS 1
# define FAILURE -1

typedef enum e_direction
{
	NORTH = 0,
	SOUTH,
	WEST,
	EAST
}	t_direction;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	int		map_x;
	int		map_y;

	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;

	int		step_x;
	int		step_y;

	int		hit;
	int		side;

	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_player	player;
	int			floor_color;
	int			ceiling_color;
	char		*textures[4];
}	t_game;

char	**read_file_lines(const char *filename, int *line_count);
int		parse_file(t_game *game, const char *filename);
void	free_lines(char **lines, int count);
void	free_arr(char **arr);
char 	*ft_trim(const char *str);
int		ft_arrlen(char **arr);

void	log_err(char *error_msg);
void	init_game(t_game *game);
void	free_game(t_game *game);

#endif