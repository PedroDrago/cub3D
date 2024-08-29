#include "../includes/cub3d.h"

void clear_textures(t_game *game)
{
	mlx_destroy_image(game->mlx, game->textures[NORTH].img);
	mlx_destroy_image(game->mlx, game->textures[SOUTH].img);
	mlx_destroy_image(game->mlx, game->textures[EAST].img);
	mlx_destroy_image(game->mlx, game->textures[WEST].img);
}

void	free_map(t_map *map)
{
	free_split(map->map);
	free_split(map->mini_map);
	free_split(map->map_file_array);
	free(map->north_path);
	free(map->south_path);
	free(map->west_path);
	free(map->east_path);
	free(map->ceiling_rgb); // NOTE: This was not suposed to be a double free, but it is. I believe some structure have another pointer to this memory and some `free_split()` call frees this string, but IDK.
	free(map->floor_rgb);
}

void mlx_clean(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	clear_textures(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

int	clean_exit(t_game *game)
{
	mlx_clean(game);
	free_map(&game->map);
	exit(1);
}
