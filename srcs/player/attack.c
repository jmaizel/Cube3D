/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:47:10 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:30:16 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Vérifie si le monstre est dans le champ de vision */
int	is_monster_in_view_angle(double angle_diff)
{
	return (angle_diff < (M_PI / 3));
}

/* Calcule l'angle vers le monstre */
double	calculate_monster_angle(t_game *game, int monster_idx)
{
	double	dx;
	double	dy;
	double	angle;
	double	player_angle;
	double	angle_diff;

	dx = game->monsters[monster_idx].x - game->player.x;
	dy = game->monsters[monster_idx].y - game->player.y;
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
	return (angle_diff);
}

/* Vérifie si le monstre est à portée d'attaque */
int	is_monster_in_range(t_game *game, int monster_idx, double max_range)
{
	double	dx;
	double	dy;
	double	distance;

	dx = game->monsters[monster_idx].x - game->player.x;
	dy = game->monsters[monster_idx].y - game->player.y;
	distance = sqrt(dx * dx + dy * dy);
	return (distance <= max_range);
}

/* Attaque un monstre spécifique */
void	attack_monster(t_game *game, int monster_idx, double distance)
{
    (void) distance;
	double	angle_diff;

	angle_diff = calculate_monster_angle(game, monster_idx);
	if (is_monster_in_view_angle(angle_diff))
	{
		game->monsters[monster_idx].health -= game->weapon_damage;
		game->monsters[monster_idx].hit_animation = 1;
		game->monsters[monster_idx].hit_timer = 0.2;
		if (game->monsters[monster_idx].health <= 0)
		{
			game->monsters[monster_idx].alive = 0;
			ft_printf("Monstre %d tué!\n", monster_idx);
		}
	}
}

/* Exécute une attaque avec l'arme */
void	attack(t_game *game)
{
	int	i;

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
		if (is_monster_in_range(game, i, game->weapon_range))
			attack_monster(game, i, 0);
		i++;
	}
}