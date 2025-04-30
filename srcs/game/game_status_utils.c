/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_status_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:18:06 by cdedessu          #+#    #+#             */
/*   Updated: 2025/04/30 17:18:39 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Vérifie si tous les monstres ont été tués pour ouvrir la porte
 * 
 * @param game Structure principale du jeu
 */
void	check_monsters_status(t_game *game)
{
	if (!game->all_monsters_killed && all_monsters_dead(game))
	{
		game->all_monsters_killed = 1;
		game->door_opened = 1;
		game->victory_timer = 3.0;
		game->victory_displayed = 1;
		ft_printf("Tous les monstres ont été éliminés! La porte est ouverte!\n");
	}
}

/**
 * Trouve la position de la porte dans la map
 * 
 * @param game Structure principale du jeu
 * @param door_x Pointeur pour stocker la position X de la porte
 * @param door_y Pointeur pour stocker la position Y de la porte
 * @return 1 si la porte est trouvée, 0 sinon
 */
int	find_door_position(t_game *game, int *door_x, int *door_y)
{
	int	y;
	int	x;

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

/**
 * Affiche le message de victoire finale 
 * 
 * @param game Structure principale du jeu
 * @return 0 pour indiquer la fin du jeu
 */
int	display_victory(t_game *game)
{
	ft_printf("VICTOIRE! Vous avez traversé la porte et terminé le jeu!\n");
	game->victory_displayed = 2;
	render_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	mlx_string_put(game->mlx, game->win, WIN_WIDTH / 2 - 200,
		WIN_HEIGHT / 2 - 40, 0xFFFF00, "FÉLICITATIONS!");
	mlx_string_put(game->mlx, game->win, WIN_WIDTH / 2 - 200,
		WIN_HEIGHT / 2, 0xFFFF00, "VOUS AVEZ TERMINÉ LE JEU!");
	usleep(2000000);
	close_window(game);
	return (0);
}

/**
 * Vérifie si le joueur a atteint la porte pour gagner
 * 
 * @param game Structure principale du jeu
 * @return 0 si le jeu continue, valeur de display_victory sinon
 */
int	check_door_victory(t_game *game)
{
	int		door_x;
	int		door_y;
	double	dx;
	double	dy;
	double	distance;

	if (!game->door_opened || game->victory_displayed == 2)
		return (0);
	if (!find_door_position(game, &door_x, &door_y))
		return (0);
	dx = game->player.x - (door_x + 0.5);
	dy = game->player.y - (door_y + 0.5);
	distance = sqrt(dx * dx + dy * dy);
	if (distance < 1.0)
		return (display_victory(game));
	return (0);
}

/**
 * Met à jour le timer de victoire
 * 
 * @param game Structure principale du jeu
 */
void	update_victory_timer(t_game *game)
{
	if (game->victory_timer > 0)
	{
		game->victory_timer -= game->delta_time;
		if (game->victory_timer <= 0)
		{
			game->victory_timer = 0;
			if (game->victory_displayed == 1)
				game->victory_displayed = 0;
		}
	}
}
