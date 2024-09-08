/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:47:09 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 20:47:09 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_map(char **map, t_vector_d fut_pos, int curr_x, int curr_y)
{
	if (curr_x != fut_pos.x || curr_y != fut_pos.y
		&& is_empty_tile(map[(int)curr_x][(int)curr_y]))
	{
		map[(int)curr_x][(int)curr_y] = '0';
		map[(int)fut_pos.x][(int)fut_pos.y] = 'P';
	}
}

void	walk_forward(t_camera *cam, char **map, char **minimap)
{
	t_vector_d	fut_pos;
	int			curr_x;
	int			curr_y;

	fut_pos.x = cam->pos.x + cam->dir.x * cam->mov_speed;
	fut_pos.y = cam->pos.y + cam->dir.y * cam->mov_speed;
	curr_y = (int)(cam->pos.y);
	curr_x = (int)(cam->pos.x);
	if (!is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y])
		|| !is_empty_tile(map[(int)(fut_pos.x - 0.2)][curr_y]))
		fut_pos.x = cam->pos.x;
	if (cam->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x)][curr_y]))
		cam->pos.x = fut_pos.x;
	else if (cam->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x)][curr_y]))
		cam->pos.x = fut_pos.x;
	if (!is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y + 0.2)])
		|| !is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y - 0.2)]))
		fut_pos.y = cam->pos.y;
	if (cam->dir.y > 0.2
		&& is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y)]))
		cam->pos.y = fut_pos.y;
	else if (cam->dir.y < 0.2
		&& is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y)]))
		cam->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}

void	walk_backwards(t_camera *cam, char **map, char **minimap)
{
	t_vector_d	fut_pos;
	int			curr_x;
	int			curr_y;

	fut_pos.x = cam->pos.x - cam->dir.x * cam->mov_speed;
	fut_pos.y = cam->pos.y - cam->dir.y * cam->mov_speed;
	curr_x = (int)(cam->pos.x);
	curr_y = (int)(cam->pos.y);
	if (!is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y])
		|| !is_empty_tile(map[(int)(fut_pos.x - 0.2)][curr_y]))
		fut_pos.x = cam->pos.x;
	if (cam->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x)][curr_y]))
		cam->pos.x = fut_pos.x;
	else if (cam->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x)][curr_y]))
		cam->pos.x = fut_pos.x;
	if (!is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y + 0.2)])
		|| !is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y - 0.2)]))
		fut_pos.y = cam->pos.y;
	if (cam->dir.y > 0.2
		&& is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y)]))
		cam->pos.y = fut_pos.y;
	else if (cam->dir.y < 0.2
		&& is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y)]))
		cam->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}

void	walk_left(t_camera *cam, char **map, char **minimap)
{
	int			curr_x;
	int			curr_y;
	t_vector_d	fut_pos;

	fut_pos.x = cam->pos.x - cam->plane.x * cam->mov_speed;
	fut_pos.y = cam->pos.y - cam->plane.y * cam->mov_speed;
	curr_x = (int)(cam->pos.x);
	curr_y = (int)(cam->pos.y);
	if (!is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y])
		|| !is_empty_tile(map[(int)(fut_pos.x - 0.2)][curr_y]))
		fut_pos.x = cam->pos.x;
	if (cam->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x)][curr_y]))
		cam->pos.x = fut_pos.x;
	else if (cam->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x)][curr_y]))
		cam->pos.x = fut_pos.x;
	if (!is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y + 0.2)])
		|| !is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y - 0.2)]))
		fut_pos.y = cam->pos.y;
	if (cam->dir.y > 0.2
		&& is_empty_tile(map[curr_x][(int)(fut_pos.y)]))
		cam->pos.y = fut_pos.y;
	else if (cam->dir.y < 0.2
		&& is_empty_tile(map[curr_x][(int)(fut_pos.y)]))
		cam->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}

void	walk_right(t_camera *cam, char **map, char **minimap)
{
	int			curr_x;
	int			curr_y;
	t_vector_d	fut_pos;

	fut_pos.x = cam->pos.x + cam->plane.x * cam->mov_speed;
	fut_pos.y = cam->pos.y + cam->plane.y * cam->mov_speed;
	curr_x = (int)(cam->pos.x);
	curr_y = (int)(cam->pos.y);
	if (!is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y])
		|| !is_empty_tile(map[(int)(fut_pos.x - 0.2)][curr_y]))
		fut_pos.x = cam->pos.x;
	if (cam->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x)][curr_y]))
		cam->pos.x = fut_pos.x;
	else if (cam->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x)][curr_y]))
		cam->pos.x = fut_pos.x;
	if (!is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y + 0.2)])
		|| !is_empty_tile(map[(int)(cam->pos.x)][(int)(fut_pos.y - 0.2)]))
		fut_pos.y = cam->pos.y;
	if (cam->dir.y > 0.2
		&& is_empty_tile(map[curr_x][(int)(fut_pos.y)]))
		cam->pos.y = fut_pos.y;
	else if (cam->dir.y < 0.2
		&& is_empty_tile(map[curr_x][(int)(fut_pos.y)]))
		cam->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}
