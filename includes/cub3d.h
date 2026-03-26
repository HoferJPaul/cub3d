#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define WIDTH 1280
# define HEIGHT 720

# ifdef __linux__
#  define KEY_ESC 65307
# else
#  define KEY_ESC 53
# endif

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
	void	*img_ptr;
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


int		close_game(t_game *game);
int		key_hook(int keycode, t_game *game);
int		render(t_game *game);

void	put_pixel(t_img *img, int x, int y, int color);
void	draw_background(t_game *game);

#endif