/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:46:34 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:23:13 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Bascule entre les modes de contrôle souris activé/désactivé */
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

/* Gère le déplacement de la souris pour la rotation caméra */
int	mouse_move(int x, int y, t_game *game)
{
	int		delta_x;
	double	rotation_angle;
	double	old_dir_x;
	double	old_plane_x;

	if (!game->mouse_enabled)
		return (0);
	(void)y;
	game->mouse_prev_x = game->mouse_x;
	game->mouse_x = x;
	delta_x = game->mouse_x - game->mouse_prev_x;
	if (delta_x != 0)
	{
		rotation_angle = delta_x * game->mouse_sensitivity;
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
		if (game->mouse_x < 100 || game->mouse_x > WIN_WIDTH - 100)
		{
			game->mouse_x = WIN_WIDTH / 2;
			game->mouse_prev_x = WIN_WIDTH / 2;
			mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		}
	}
	return (0);
}

/* Gère le clic de souris */
int	mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		attack(game);
	}
	return (0);
}

/* Gère l'appui sur une touche */
int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 1;
	if (keycode == 65361 || keycode == 123)
		game->rotate_left = 1;
	else if (keycode == 65363 || keycode == 124)
		game->rotate_right = 1;
	else if (keycode == 65307 || keycode == 53)
		close_window(game);
	else if (keycode == 109 || keycode == 46)
		toggle_mouse(game);
	else if (keycode == 32 || keycode == 1)
		attack(game);
	return (0);
}

/* Gère le relâchement d'une touche */
int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 0;
	if (keycode == 65361 || keycode == 123)
		game->rotate_left = 0;
	else if (keycode == 65363 || keycode == 124)
		game->rotate_right = 0;
	return (0);
}