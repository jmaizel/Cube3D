/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:12:03 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/14 10:58:24 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	exit_error(char *msg)
{
	ft_printf("%s\n", msg);
	return (0);
}

static void	draw_final_victory(t_game *game, int msg_x, int msg_y, int color)
{
	mlx_string_put(game->mlx, game->win, msg_x, msg_y - 40, 0xFFFF00,
		"CONGRATULATIONS !");
	mlx_string_put(game->mlx, game->win, msg_x, msg_y, 0xFFFF00,
		"YOU'VE COMPLETED THE GAME !");
	mlx_string_put(game->mlx, game->win, msg_x, msg_y + 40, color,
		"Press ESC to exit");
}

void	draw_victory_message(t_game *game)
{
	int	msg_x;
	int	msg_y;
	int	color;

	msg_x = WIN_WIDTH / 2 - 150;
	msg_y = WIN_HEIGHT / 2;
	color = 0xFF0000;
	if (game->victory_displayed)
	{
		if (game->victory_final)
			draw_final_victory(game, msg_x, msg_y, color);
		else
		{
			mlx_string_put(game->mlx, game->win, WIN_WIDTH - 300, WIN_HEIGHT
				- 60, color, "ALL MONSTERS ARE ELIMINATED !");
			mlx_string_put(game->mlx, game->win, WIN_WIDTH - 300, WIN_HEIGHT
				- 40, color, "THE DOOR IS OPEN !");
		}
	}
	else if (game->all_monsters_killed && game->door_opened)
	{
		mlx_string_put(game->mlx, game->win, 30, WIN_HEIGHT - 30, color,
			"Open door - Go through it to finish");
	}
}
