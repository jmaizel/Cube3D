/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:12:00 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:31:47 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Recherche la position de la porte dans la map */
int	find_door_position(t_game *game, int *door_x, int *door_y)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == 'D')
			{
				*door_x = x;
				*door_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

/* Vérifie si le joueur a gagné (traversé la porte ouverte) */
int	check_victory_condition(t_game *game)
{
	int	door_x;
	int	door_y;
	int	door_found;

	if (!game->door_opened || game->victory_displayed == 2)
		return (0);
	door_found = find_door_position(game, &door_x, &door_y);
	if (door_found)
	{
		if (check_door_proximity(game, door_x, door_y))
			return (1);
	}
	return (0);
}

/* Affiche le message final et attend que le joueur quitte */
void	display_final_message(t_game *game)
{
	int	msg_x;
	int	msg_y;

	msg_x = WIN_WIDTH / 2 - 150;
	msg_y = WIN_HEIGHT / 2;
	mlx_string_put(game->mlx, game->win, msg_x, msg_y - 40, 0xFFFF00,
		"FÉLICITATIONS!");
	mlx_string_put(game->mlx, game->win, msg_x, msg_y, 0xFFFF00,
		"VOUS AVEZ TERMINÉ LE JEU!");
	mlx_string_put(game->mlx, game->win, msg_x, msg_y + 40, 0x00FF00,
		"Appuyez sur ESC pour quitter");
}