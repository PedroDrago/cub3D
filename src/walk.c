#include "../includes/cub3d.h"

void	update_map(char **map, t_vector_d fut_pos, int curr_x, int curr_y)
{
	if (curr_x != fut_pos.x || curr_y != fut_pos.y)
	{
		map[(int)curr_x][(int)curr_y] = '0';
		map[(int)fut_pos.x][(int)fut_pos.y] = 'P';
	}
}

void	walk_forward(t_camera *camera, char **map, char **minimap)
{
	t_vector_d	fut_pos;
	int			diagonal_dir;
	int			curr_x;
	int			curr_y;

	fut_pos.x = camera->pos.x + camera->dir.x * camera->mov_speed;
	fut_pos.y = camera->pos.y + camera->dir.y * camera->mov_speed;
	diagonal_dir = get_diagonal_dir(camera->pos, fut_pos);
	if (map[(int)(fut_pos.x)][(int)(fut_pos.y)] == '1')
		return ;
	curr_x = (int)(camera->pos.x);
	curr_y = (int)(camera->pos.y);
	if (!is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y]))
		fut_pos.x = camera->pos.x;
	if (camera->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x
				+ 0.2)][curr_y]))
		camera->pos.x = fut_pos.x;
	else if (camera->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x
				- 0.2)][curr_y]))
		camera->pos.x = fut_pos.x;
	if (!is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)]))
		fut_pos.y = camera->pos.y;
	if (camera->dir.y > 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y
			+ 0.2)]))
		camera->pos.y = fut_pos.y;
	else if (camera->dir.y < 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y
			- 0.2)]))
		camera->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}

void	walk_backwards(t_camera *camera, char **map, char **minimap)
{
	int			curr_x;
	int			curr_y;
	t_vector_d	fut_pos;

	fut_pos.x = camera->pos.x - camera->dir.x * camera->mov_speed;
	fut_pos.y = camera->pos.y - camera->dir.y * camera->mov_speed;
	curr_x = (int)(camera->pos.x);
	curr_y = (int)(camera->pos.y);
	if (map[(int)(fut_pos.x)][(int)(fut_pos.y)] == '1')
		return ;
	if (camera->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x
				- 0.2)][curr_y]) && is_empty_tile(map[(int)(fut_pos.x
				+ 0.2)][curr_y]))
		camera->pos.x = fut_pos.x;
	else if (camera->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x
				+ 0.2)][curr_y]) && is_empty_tile(map[(int)(fut_pos.x
				- 0.2)][curr_y]))
		camera->pos.x = fut_pos.x;
	if (camera->dir.y > 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y
			- 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)]))
		camera->pos.y = fut_pos.y;
	else if (camera->dir.y < 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y
			+ 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y - 0.2)]))
		camera->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}

void	walk_left(t_camera *camera, char **map, char **minimap)
{
	int			curr_x;
	int			curr_y;
	t_vector_d	fut_pos;

	fut_pos.x = camera->pos.x - camera->plane.x * camera->mov_speed;
	fut_pos.y = camera->pos.y - camera->plane.y * camera->mov_speed;
	curr_x = (int)(camera->pos.x);
	curr_y = (int)(camera->pos.y);
	if (map[(int)(fut_pos.x)][(int)(fut_pos.y)] == '1')
		return ;
	if (camera->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x
				- 0.2)][curr_y]) && is_empty_tile(map[(int)(fut_pos.x
				+ 0.2)][curr_y]))
		camera->pos.x = fut_pos.x;
	else if (camera->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x
				+ 0.2)][curr_y]) && is_empty_tile(map[(int)(fut_pos.x
				- 0.2)][curr_y]))
		camera->pos.x = fut_pos.x;
	if (camera->dir.y > 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y
			+ 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y - 0.2)]))
		camera->pos.y = fut_pos.y;
	else if (camera->dir.y < 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y
			- 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)]))
		camera->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}

void	walk_right(t_camera *camera, char **map, char **minimap)
{
	int			curr_x;
	int			curr_y;
	t_vector_d	fut_pos;

	fut_pos.x = camera->pos.x + camera->plane.x * camera->mov_speed;
	fut_pos.y = camera->pos.y + camera->plane.y * camera->mov_speed;
	curr_x = (int)(camera->pos.x);
	curr_y = (int)(camera->pos.y);
	if (map[(int)(fut_pos.x)][(int)(fut_pos.y)] == '1')
		return ;
	if (camera->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x
				+ 0.2)][curr_y]) && is_empty_tile(map[(int)(fut_pos.x
				- 0.2)][curr_y]))
		camera->pos.x = fut_pos.x;
	else if (camera->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x
				- 0.2)][curr_y]) && is_empty_tile(map[(int)(fut_pos.x
				+ 0.2)][curr_y]))
		camera->pos.x = fut_pos.x;
	if (camera->dir.y > 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y
			+ 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y - 0.2)]))
		camera->pos.y = fut_pos.y;
	else if (camera->dir.y < 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y
			- 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)]))
		camera->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}
