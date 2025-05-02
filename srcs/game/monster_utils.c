/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:42:41 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/02 19:47:22 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Met à jour les effets de coup pour les monstres
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
