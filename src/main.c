#include <unistd.h>
#include "libft.h"
#include "cub3d.h"
#include "parser.h"

int main(int argc, char **argv)
{
    printf(
        "  ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ \n"
        " ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\n"
        " ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\n"
        " ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\n"
        " ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\n"
        "  ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ \n"
        "\n"
        "        42 - cub3D | Raycasting Engine\n"
    );

	t_game game;

	init_game(&game);

	if (argc != 2)
	{
		printf("Usage: ./cub3d map.cub\n");
		return 1;
	}
	char *filename = argv[1];
	int line_count;
	char **lines = read_file_lines(filename, &line_count);
	if (!lines)
		return (1);
	parse_file(&game, argv[1]);
	printf("floor color: %i\n", game.floor_color);
	printf("ceiling color: %i\n", game.ceiling_color);
	printf("NO: %s\n", game.textures[NORTH]);
	printf("SO: %s\n", game.textures[SOUTH]);
	printf("EA: %s\n", game.textures[EAST]);
	printf("WE: %s\n", game.textures[WEST]);

	for (int i = 0; i < game.map.height; i++)
        printf("%s\n", game.map.grid[i]);
	free_game(&game);
    return 0;
}
