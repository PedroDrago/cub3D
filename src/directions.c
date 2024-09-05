/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:02:08 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 21:02:08 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_south(t_camera *camera)
{
	camera->dir.x = -1;
	camera->dir.y = 0;
	camera->plane.x = 0;
	camera->plane.y = 0.66;
}

void	set_north(t_camera *camera)
{
	camera->dir.x = 1;
	camera->dir.y = 0;
	camera->plane.x = 0;
	camera->plane.y = -0.66;
}

void	set_east(t_camera *camera)
{
	camera->dir.x = 0;
	camera->dir.y = -1;
	camera->plane.x = -0.66;
	camera->plane.y = 0;
}

void	set_west(t_camera *camera)
{
	camera->dir.x = 0;
	camera->dir.y = 1;
	camera->plane.x = 0.66;
	camera->plane.y = 0;
}
