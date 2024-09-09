/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:01:35 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 21:03:14 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_camera_dir(t_camera *camera, char **map)
{
	if (map[(int)camera->pos.x][(int)camera->pos.y] == 'S')
		set_south(camera);
	else if (map[(int)camera->pos.x][(int)camera->pos.y] == 'N')
		set_north(camera);
	else if (map[(int)camera->pos.x][(int)camera->pos.y] == 'E')
		set_east(camera);
	else if (map[(int)camera->pos.x][(int)camera->pos.y] == 'W')
		set_west(camera);
}

void	init_camera(t_camera *camera, t_game *game)
{
	camera->mov_speed = 0.5;
	camera->rot_speed = 0.2;
	get_initial_pos(game->map.map, &camera->pos);
	set_camera_dir(camera, game->map.map);
	game->map.map[(int)camera->pos.x][(int)camera->pos.y] = 'P';
}
