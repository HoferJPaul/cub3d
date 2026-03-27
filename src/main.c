#include <unistd.h>
#include "libft.h"
#include "cub3d.h"
#include <stdio.h>

int main()
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

	char **lines;
    int count;

    lines = read_file_lines("maps/sub.cub", &count);
    if (!lines)
    {
        printf("Failed to read file\n");
        return 1;
    }

    for (int i = 0; i < count; i++)
        printf("%s\n", lines[i]);

    int floor = parse_rgb_line(find_floor_line(lines, count));
    int ceiling = parse_rgb_line(find_ceiling_line(lines, count));

    printf("Floor color: %d\n", floor);
    printf("Ceiling color: %d\n", ceiling);

    free_lines(lines, count);
    return 0;
}
