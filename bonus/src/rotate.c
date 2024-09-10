/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:00:50 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/03 20:13:16 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_right(t_camera *camera)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = camera->rot_speed;
	old_dir_x = camera->dir.x;
	old_plane_x = camera->plane.x;
	camera->dir.x = camera->dir.x * cos(-rot) - camera->dir.y * sin(-rot);
	camera->dir.y = old_dir_x * sin(-rot) + camera->dir.y * cos(-rot);
	camera->plane.x = camera->plane.x * cos(-rot) - (camera->plane.y
			* sin(-rot));
	camera->plane.y = old_plane_x * sin(-rot) + camera->plane.y * cos(-rot);
	return ;
}

void	slowly_rotate_right(t_camera *camera)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = camera->rot_speed / 35;
	old_dir_x = camera->dir.x;
	old_plane_x = camera->plane.x;
	camera->dir.x = camera->dir.x * cos(-rot) - camera->dir.y * sin(-rot);
	camera->dir.y = old_dir_x * sin(-rot) + camera->dir.y * cos(-rot);
	camera->plane.x = camera->plane.x * cos(-rot) - (camera->plane.y
			* sin(-rot));
	camera->plane.y = old_plane_x * sin(-rot) + camera->plane.y * cos(-rot);
	return ;
}

void	rotate_left(t_camera *camera)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = camera->rot_speed;
	old_dir_x = camera->dir.x;
	old_plane_x = camera->plane.x;
	camera->dir.x = camera->dir.x * cos(rot) - camera->dir.y * sin(rot);
	camera->dir.y = old_dir_x * sin(rot) + camera->dir.y * cos(rot);
	camera->plane.x = camera->plane.x * cos(rot) - (camera->plane.y * sin(rot));
	camera->plane.y = old_plane_x * sin(rot) + camera->plane.y * cos(rot);
	return ;
}

void	slowly_rotate_left(t_camera *camera)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = camera->rot_speed / 35;
	old_dir_x = camera->dir.x;
	old_plane_x = camera->plane.x;
	camera->dir.x = camera->dir.x * cos(rot) - camera->dir.y * sin(rot);
	camera->dir.y = old_dir_x * sin(rot) + camera->dir.y * cos(rot);
	camera->plane.x = camera->plane.x * cos(rot) - (camera->plane.y * sin(rot));
	camera->plane.y = old_plane_x * sin(rot) + camera->plane.y * cos(rot);
	return ;
}
