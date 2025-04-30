/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:12:03 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:16:04 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Libère la mémoire allouée pour la map */
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

/* Affiche un message d'erreur et retourne 0 */
int	exit_error(char *msg)
{
	ft_printf("%s\n", msg);
	return (0);
}

/* Ferme la fenêtre et libère toutes les ressources allouées */
int	close_window(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free_map(game->map.grid);
	exit(0);
	return (0);
}

/* Affiche le message de victoire quand les monstres sont éliminés */
void	draw_victory_part1(t_game *game, int msg_x, int msg_y, int color)
{
	if (game->victory_displayed)
	{
		if (game->victory_final)
		{
			mlx_string_put(game->mlx, game->win, msg_x, msg_y - 40, 0xFFFF00,
				"FÉLICITATIONS!");
			mlx_string_put(game->mlx, game->win, msg_x, msg_y, 0xFFFF00,
				"VOUS AVEZ TERMINÉ LE JEU!");
			mlx_string_put(game->mlx, game->win, msg_x, msg_y + 40, color,
				"Appuyez sur ESC pour quitter");
		}
		else
		{
			mlx_string_put(game->mlx, game->win, msg_x, msg_y, color,
				"TOUS LES MONSTRES SONT ELIMINES!");
			mlx_string_put(game->mlx, game->win, msg_x, msg_y + 30, color,
				"LA PORTE EST OUVERTE!");
		}
	}
}

/* Affiche un message de victoire quand tous les monstres sont éliminés */
void	draw_victory_message(t_game *game)
{
	int	msg_x;
	int	msg_y;
	int	color;

	msg_x = WIN_WIDTH / 2 - 150;
	msg_y = WIN_HEIGHT / 2;
	color = 0x00FF00;
	draw_victory_part1(game, msg_x, msg_y, color);
	if (game->all_monsters_killed && game->door_opened
		&& !game->victory_displayed)
	{
		mlx_string_put(game->mlx, game->win, 30, WIN_HEIGHT - 30, color,
			"Porte ouverte - Traversez-la pour terminer");
	}
}

/* Obtient le temps actuel en secondes */
double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}