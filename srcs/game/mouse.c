/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:46:34 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/02 19:36:47 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Applique la rotation à partir d'un angle
 */
static void	apply_rotation(t_game *game, double rotation_angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(rotation_angle)
		- game->player.dir_y * sin(rotation_angle);
	game->player.dir_y = old_dir_x * sin(rotation_angle)
		+ game->player.dir_y * cos(rotation_angle);
	game->player.plane_x = game->player.plane_x * cos(rotation_angle)
		- game->player.plane_y * sin(rotation_angle);
	game->player.plane_y = old_plane_x * sin(rotation_angle)
		+ game->player.plane_y * cos(rotation_angle);
}

/**
 * Gère les mouvements de la souris pour contrôler la rotation du joueur
 */
int	mouse_move(int x, int y, t_game *game)
{
	int		delta_x;
	double	rotation_angle;

	if (!game->mouse_enabled)
		return (0);
	(void)y;
	game->mouse_prev_x = game->mouse_x;
	game->mouse_x = x;
	delta_x = game->mouse_x - game->mouse_prev_x;
	if (delta_x != 0)
	{
		rotation_angle = delta_x * game->mouse_sensitivity;
		apply_rotation(game, rotation_angle);
		if (game->mouse_x < 100 || game->mouse_x > WIN_WIDTH - 100)
		{
			game->mouse_x = WIN_WIDTH / 2;
			game->mouse_prev_x = WIN_WIDTH / 2;
			mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		}
	}
	return (0);
}

/**
 * Active ou désactive le mode de contrôle à la souris
 */
void	toggle_mouse(t_game *game)
{
	game->mouse_enabled = !game->mouse_enabled;
	if (game->mouse_enabled)
	{
		mlx_mouse_hide(game->mlx, game->win);
		mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		game->mouse_x = WIN_WIDTH / 2;
		game->mouse_prev_x = WIN_WIDTH / 2;
	}
	else
	{
		mlx_mouse_show(game->mlx, game->win);
	}
}

/**
 * Gère les clics de souris
 */
int	mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		attack(game);
	return (0);
}
