/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:13:51 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/03 20:13:52 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_empty_tile(char c)
{
	return (c == '0' || c == 'P' || c == 'O');
}

int	get_diagonal_dir(t_vector_d pos, t_vector_d fut_pos)
{
	if (pos.x < fut_pos.x && pos.y < fut_pos.y)
		return (2);
	else if (pos.x < fut_pos.x && pos.y > fut_pos.y)
		return (1);
	else if (pos.x > fut_pos.x && pos.y > fut_pos.y)
		return (3);
	else if (pos.x > fut_pos.x && pos.y < fut_pos.y)
		return (4);
	return (0);
}
