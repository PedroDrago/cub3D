#include "../../includes/cub3d.h"

int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	error_exit(int status, char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(status);
}
