#include "../includes/cub3d.h"

void	set_cam_pos(t_vector_i *pos, int new_x, int new_y)
{
	pos->x = new_x;
	pos->y = new_y;
}

int	get_cam_pos(t_game *game, t_vector_i *pos)
{
	t_vector_i	player;

	player.x = game->camera.pos.x;
	player.y = game->camera.pos.y;
	if (game->map.map[player.x + 1][player.y] == 'C' || game->map.map[player.x
		+ 1][player.y] == 'O' || game->map.map[player.x + 1][player.y] == 'L')
		set_cam_pos(pos, player.x + 1, player.y);
	else if (game->map.map[player.x - 1][player.y] == 'C'
		|| game->map.map[player.x - 1][player.y] == 'O'
		|| game->map.map[player.x - 1][player.y] == 'L')
		set_cam_pos(pos, player.x - 1, player.y);
	else if (game->map.map[player.x][player.y + 1] == 'C'
		|| game->map.map[player.x][player.y + 1] == 'O'
		|| game->map.map[player.x][player.y + 1] == 'L')
		set_cam_pos(pos, player.x, player.y + 1);
	else if (game->map.map[player.x][player.y - 1] == 'C'
		|| game->map.map[player.x][player.y - 1] == 'O'
		|| game->map.map[player.x][player.y - 1] == 'L')
		set_cam_pos(pos, player.x, player.y - 1);
	else
		return (0);
	return (1);
}

// FIX: rename this to validate_doors
int	validate_doors(t_game *game, t_vector_i pos)
{
	char		**copy_map;
	t_vector_i	dim;

	copy_map = duplicate_map_bordered(game->map.map, game->map.height,
			game->map.width);
	if (!copy_map)
		return (0);
	dim.x = game->map.height + 2;
	dim.y = game->map.width + 1;
	ft_floodfill(copy_map, 0, 0, dim);
	if ((copy_map[(int)pos.x][(int)pos.y + 1] == '2')
		|| (copy_map[(int)pos.x][(int)pos.y - 1] == '2') || (copy_map[(int)pos.x
			+ 1][(int)pos.y] == '2') || (copy_map[(int)pos.x
			- 1][(int)pos.y] == '2'))
	{
		free_split(copy_map);
		return (1);
	}
	free_split(copy_map);
	game->map.map[pos.x][pos.y] = 'O';
	game->map.mini_map[pos.x][pos.y] = 'O';
	return (1);
}

int	toggle_door(t_game *game)
{
	t_vector_i	pos;

	pos.x = (int)(game->camera.pos.x);
	pos.y = (int)(game->camera.pos.y);
	if (!get_cam_pos(game, &pos))
		return (1);
	else if (game->map.map[pos.x][pos.y] == 'L')
	{
		game->map.map[pos.x][pos.y] = '0';
		game->map.mini_map[pos.x][pos.y] = '0';
	}
	else if (game->map.map[pos.x][pos.y] == 'O')
	{
		game->map.map[pos.x][pos.y] = 'C';
		game->map.mini_map[pos.x][pos.y] = 'C';
	}
	else if (game->map.map[pos.x][pos.y] == 'C')
		return (validate_doors(game, pos));
	return (1);
}
