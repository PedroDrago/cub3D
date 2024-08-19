#include "../../includes/cub3d.h"

void	get_map(t_game *game, char *file)
{
	int	hold;

	if (!check_extension(file))
		exit_printing(1, "Error\nWrong extension\n");
	init_map(&game->map);
	if (!get_map_proportions(&game->map, file))
		exit_printing(1, "Error\nFile not found\n");
	if (!read_map_file(&game->map, file))
		exit_printing(1, "Error\nInternal Error\n");
	if (!parse_map(&game->map))
	{
		free_map(&game->map);
		exit(1);
	}
	fill_spaces_with_zero(game->map.map, game->map.height, game->map.width);
	if (!validate_map(game->map.map, game->map.height, game->map.width))
	{
		free_map(&game->map);
		printf("Error at validate_map\n");
		exit(1);
	}
	free_split(game->map.map_file_array);
	game->map.map_file_array = NULL;
	game->map.floor_color = rgb_to_hex(game->map.floor_rgb);
	hold = rgb_to_hex(game->map.floor_rgb);
	if (hold < 0)
	{
		free_map(&game->map);
		printf("Error at color formatting\n");
	}
	game->map.floor_color = hold;
	hold = rgb_to_hex(game->map.ceiling_rgb);
	if (hold < 0)
	{
		free_map(&game->map);
		printf("Error at color formatting\n");
	}
	game->map.ceiling_color = hold;
	free(game->map.floor_rgb);
	free(game->map.ceiling_rgb);
	if (!files_exist(&game->map))
	{
		free_map(&game->map);
		printf("Error at files_exist\n");
		exit(1);
	}
	game->map.mini_map = duplicate_map(game->map.map, game->map.height);
	// print_split(game->map.mini_map);
}
