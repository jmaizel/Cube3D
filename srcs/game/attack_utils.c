/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:13:34 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/02 19:37:32 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Normalise un angle entre -PI et PI
 */
void	normalize_angle(double *angle)
{
	while (*angle > M_PI)
		*angle -= 2 * M_PI;
	while (*angle < -M_PI)
		*angle += 2 * M_PI;
}

/**
 * Initialise les états d'animation de l'arme
 */
void	init_weapon_animation(t_game *game)
{
	game->firing = 1;
	game->weapon_timer = game->weapon_cooldown;
	game->weapon_animating = 1;
	game->current_weapon_frame = 0;
	game->weapon_anim_time = 0;
}

/**
 * Vérifie si un monstre est visible dans le champ de vision
 */
int	is_monster_in_fov(t_game *game, double dx, double dy)
{
	double	angle;
	double	player_angle;
	double	angle_diff;

	angle = atan2(dy, dx);
	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	normalize_angle(&angle);
	normalize_angle(&player_angle);
	angle_diff = fabs(angle - player_angle);
	if (angle_diff > M_PI)
		angle_diff = 2 * M_PI - angle_diff;
	return (angle_diff < (M_PI / 3));
}

/**
 * Applique des dégâts à un monstre
 */
void	damage_monster(t_game *game, int monster_index)
{
	game->monsters[monster_index].health -= game->weapon_damage;
	game->monsters[monster_index].hit_animation = 1;
	game->monsters[monster_index].hit_timer = 0.2;
	if (game->monsters[monster_index].health <= 0)
	{
		game->monsters[monster_index].alive = 0;
		ft_printf("Monstre %d tué!\n", monster_index);
	}
}
