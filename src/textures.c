#include "../includes/cub3d.h"

void load_texture(t_game *game, t_data *texture, char *path)
{
	texture->width = 0;
	texture->height = 0;
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

void init_textures(t_game *game)
{
	load_texture(game, &game->textures[NORTH], game->map.north_path);
	load_texture(game, &game->textures[SOUTH], game->map.south_path);
	load_texture(game, &game->textures[EAST], game->map.east_path);
	load_texture(game, &game->textures[WEST], game->map.west_path);
}

