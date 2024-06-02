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
	load_texture(game, &game->textures[0], "./assets/bluestone.xpm");
	load_texture(game, &game->textures[1], "./assets/graystone.xpm");
	load_texture(game, &game->textures[2], "./assets/redstone.xpm");
	load_texture(game, &game->textures[3], "./assets/yellowstone.xpm");
}
