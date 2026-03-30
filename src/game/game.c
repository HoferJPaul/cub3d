#include "../../includes/cub3d.h"

void	init_game(t_game *game)
{
	game->floor_color = 0x005500;
	game->ceiling_color = 0x87CEEB;
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		write(2, "Error\nmlx_init failed\n", 22);
		exit(EXIT_FAILURE);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
	{
		write(2, "Error\nmlx_new_window failed\n", 28);
		exit(EXIT_FAILURE);
	}
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img_ptr)
	{
		write(2, "Error\nmlx_new_image failed\n", 27);
		exit(EXIT_FAILURE);
	}
	game->img.addr = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	if (!game->img.addr)
	{
		write(2, "Error\nmlx_get_data_addr failed\n", 31);
		exit(EXIT_FAILURE);
	}
}
