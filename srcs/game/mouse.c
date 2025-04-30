/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:46:34 by cdedessu          #+#    #+#             */
/*   Updated: 2025/04/30 17:16:01 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Gère les mouvements de la souris pour contrôler la rotation du joueur
 * 
 * @param x Position x actuelle de la souris
 * @param y Position y actuelle de la souris
 * @param game Structure principale du jeu
 * @return 0 (toujours réussi)
 */
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

/**
 * Active ou désactive le mode de contrôle à la souris
 * 
 * @param game Structure principale du jeu
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
 * Gère l'attaque du joueur contre les monstres
 * 
 * @param game Structure principale du jeu
 */
void	attack(t_game *game)
{
	int		i;
	double	distance;
	double	dx;
	double	dy;
	double	angle;
	double	player_angle;
	double	angle_diff;

	if (game->weapon_timer > 0)
		return ;
	game->firing = 1;
	game->weapon_timer = game->weapon_cooldown;
	game->weapon_animating = 1;
	game->current_weapon_frame = 0;
	game->weapon_anim_time = 0;
	i = 0;
	while (i < game->monster_count)
	{
		if (!game->monsters[i].alive)
		{
			i++;
			continue ;
		}
		dx = game->monsters[i].x - game->player.x;
		dy = game->monsters[i].y - game->player.y;
		distance = sqrt(dx * dx + dy * dy);
		if (distance > game->weapon_range)
		{
			i++;
			continue ;
		}
		angle = atan2(dy, dx);
		player_angle = atan2(game->player.dir_y, game->player.dir_x);
		while (angle > M_PI)
			angle -= 2 * M_PI;
		while (angle < -M_PI)
			angle += 2 * M_PI;
		while (player_angle > M_PI)
			player_angle -= 2 * M_PI;
		while (player_angle < -M_PI)
			player_angle += 2 * M_PI;
		angle_diff = fabs(angle - player_angle);
		while (angle_diff > M_PI)
			angle_diff = 2 * M_PI - angle_diff;
		if (angle_diff < (M_PI / 3))
		{
			game->monsters[i].health -= game->weapon_damage;
			game->monsters[i].hit_animation = 1;
			game->monsters[i].hit_timer = 0.2;
			if (game->monsters[i].health <= 0)
			{
				game->monsters[i].alive = 0;
				ft_printf("Monstre %d tué!\n", i);
			}
		}
		i++;
	}
}

/**
 * Gère les clics de souris
 * 
 * @param button Bouton de la souris cliqué
 * @param x Position x du clic
 * @param y Position y du clic
 * @param game Structure principale du jeu
 * @return 0 (toujours réussi)
 */
int	mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		attack(game);
	return (0);
}