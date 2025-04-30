/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:31:16 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:21:22 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Initialise les paramètres d'un monstre à sa position */
void	setup_monster(t_game *game, int x, int y, int monster_index)
{
	game->monsters[monster_index].x = x + 0.5;
	game->monsters[monster_index].y = y + 0.5;
	game->monsters[monster_index].alive = 1;
	game->monsters[monster_index].frame = 0;
	game->monsters[monster_index].anim_time = 0.0;
	game->monsters[monster_index].anim_speed = 0.2;
	game->monsters[monster_index].health = 100;
	game->monsters[monster_index].max_health = 100;
	game->monsters[monster_index].hit_animation = 0;
	game->monsters[monster_index].hit_timer = 0.0;
}

/* Initialise les monstres dans la map */
void	init_monsters(t_game *game)
{
	int	x;
	int	y;

	game->monster_count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == 'M')
			{
				if (game->monster_frame_count == 0)
					ft_printf("Warning: Monstre trouvé mais pas de texture\n");
				setup_monster(game, x, y, game->monster_count);
				game->monster_count++;
				game->map.grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

/* Met à jour les animations des monstres */
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

/* Vérifie si tous les monstres sont morts */
int	all_monsters_dead(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->monster_count)
	{
		if (game->monsters[i].alive)
			return (0);
		i++;
	}
	return (1);
}