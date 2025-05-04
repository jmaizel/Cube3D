/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:12:03 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/04 12:12:51 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Libère la mémoire allouée pour la map
 *
 * @param map Tableau 2D représentant la map
 */
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

/**
 * Affiche un message d'erreur et retourne 0
 *
 * @param msg Message d'erreur à afficher
 * @return 0 (toujours)
 */
int	exit_error(char *msg)
{
	ft_printf("%s\n", msg);
	return (0);
}

/**
 * Ferme la fenêtre et libère toutes les ressources allouées
 *
 * @param game Structure principale du jeu
 * @return 0 (toujours)
 */
int	close_window(t_game *game)
{
	if (game->victory_tex.img)
		mlx_destroy_image(game->mlx, game->victory_tex.img);
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

/**
 * Affiche les messages de victoire finale
 *
 * @param game Structure principale du jeu
 * @param msg_x Position X du message
 * @param msg_y Position Y du message
 * @param color Couleur du message
 */
static void	draw_final_victory(t_game *game, int msg_x, int msg_y, int color)
{
	mlx_string_put(game->mlx, game->win, msg_x, msg_y - 40, 0xFFFF00,
		"FÉLICITATIONS!");
	mlx_string_put(game->mlx, game->win, msg_x, msg_y, 0xFFFF00,
		"VOUS AVEZ TERMINÉ LE JEU!");
	mlx_string_put(game->mlx, game->win, msg_x, msg_y + 40, color,
		"Appuyez sur ESC pour quitter");
}

/**
 * Affiche un message de victoire quand tous les monstres sont éliminés
 *
 * @param game Structure principale du jeu
 */
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
			mlx_string_put(game->mlx, game->win, WIN_WIDTH - 300,
				WIN_HEIGHT - 60, color, "TOUS LES MONSTRES SONT ELIMINÉS!");
			mlx_string_put(game->mlx, game->win, WIN_WIDTH - 300,
				WIN_HEIGHT - 40, color, "LA PORTE EST OUVERTE!");
		}
	}
	else if (game->all_monsters_killed && game->door_opened)
	{
		mlx_string_put(game->mlx, game->win, 30, WIN_HEIGHT - 30, color,
			"Porte ouverte - Traversez-la pour terminer");
	}
}
