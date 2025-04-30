/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:19:17 by cdedessu          #+#    #+#             */
/*   Updated: 2025/04/30 17:19:45 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Retourne le temps actuel en secondes avec précision microseconde
 * 
 * @return Temps actuel en secondes
 */
double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

/**
 * Calcule le delta time entre les frames
 * 
 * @param game Structure principale du jeu
 */
void	calculate_delta_time(t_game *game)
{
	double	current_time;

	current_time = get_time();
	if (game->last_frame_time == 0.0)
		game->last_frame_time = current_time;
	game->delta_time = current_time - game->last_frame_time;
	game->last_frame_time = current_time;
	if (game->delta_time > 0.1)
		game->delta_time = 0.1;
}

/**
 * Met à jour le timer de l'arme
 * 
 * @param game Structure principale du jeu
 */
void	update_weapon_timer(t_game *game)
{
	if (game->weapon_timer > 0)
	{
		game->weapon_timer -= game->delta_time;
		if (game->weapon_timer <= 0)
		{
			game->weapon_timer = 0;
			game->firing = 0;
		}
	}
	if (game->weapon_animating)
	{
		game->weapon_anim_time += game->delta_time;
		if (game->weapon_anim_time >= game->weapon_anim_speed)
		{
			game->weapon_anim_time -= game->weapon_anim_speed;
			game->current_weapon_frame++;
			if (game->current_weapon_frame >= game->weapon_frame_count)
			{
				game->current_weapon_frame = 0;
				game->weapon_animating = 0;
			}
		}
	}
}

/**
 * Met à jour les effets de coup pour les monstres
 * 
 * @param game Structure principale du jeu
 */
void	update_monster_hit_effects(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->monster_count)
	{
		if (game->monsters[i].hit_timer > 0)
		{
			game->monsters[i].hit_timer -= game->delta_time;
			if (game->monsters[i].hit_timer <= 0)
			{
				game->monsters[i].hit_timer = 0;
				game->monsters[i].hit_animation = 0;
			}
		}
		i++;
	}
}

/**
 * Met à jour les animations des monstres
 * 
 * @param game Structure principale du jeu
 */
void	update_monster_animations(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->monster_count)
	{
		if (game->monsters[i].alive)
		{
			game->monsters[i].anim_time += game->delta_time;
			if (game->monsters[i].anim_time >= game->monsters[i].anim_speed)
			{
				game->monsters[i].anim_time -= game->monsters[i].anim_speed;
				game->monsters[i].frame = (game->monsters[i].frame + 1)
					% game->monster_frame_count;
			}
		}
		i++;
	}
}
