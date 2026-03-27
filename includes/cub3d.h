#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# define SUCCESS 0
# define FAILURE -1

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
}	t_game;


char		**read_file_lines(const char *filename, int *line_count);
int			parse_file(t_game *game, const char *filename);
int			parse_rgb_line(const char *line);
const char	*find_floor_line(char **lines, int line_count);
const char	*find_ceiling_line(char **lines, int line_count);

#endif