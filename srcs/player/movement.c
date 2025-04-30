/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:45:10 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:22:32 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MOVE_SPEED 0.1

/* Vérifie si une position sur la map est valide (pas de mur ni hors limites) */
int	is_valid_position(t_game *game, double x, double y)
{
	if (x < 0 || y < 0 || (int)x >= game->map.width
		|| (int)y >= game->map.height)
		return (0);
	if (game->map.grid[(int)y][(int)x] == '1')
		return (0);
	if (game->map.grid[(int)y][(int)x] == 'D' && !game->door_opened)
		return (0);
	return (1);
}

/* Déplace le joueur vers l'avant */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * game->move_speed;
	new_y = game->player.y + game->player.dir_y * game->move_speed;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Déplace le joueur vers l'arrière */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Déplace le joueur vers la gauche */
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Déplace le joueur vers la droite */
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Gère tous les mouvements actifs du joueur */
void	handle_movement(t_game *game)
{
	if (game->keys[119] || game->keys[13])
		move_forward(game);
	if (game->keys[115] || game->keys[1])
		move_backward(game);
	if (game->keys[97] || game->keys[0])
		move_left(game);
	if (game->keys[100] || game->keys[2])
		move_right(game);
	if (game->rotate_left)
		rotate_left(game);
	if (game->rotate_right)
		rotate_right(game);
}