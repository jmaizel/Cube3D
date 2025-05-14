/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:30:00 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:40:21 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	render_monsters(t_game *game)
{
	int			i;
	int			order[MAX_MONSTERS];
	double		distances[MAX_MONSTERS];
	t_sprite	sprite;

	if (game->monster_frame_count == 0)
		return ;
	sort_monsters(game, distances, order);
	i = 0;
	while (i < game->monster_count)
	{
		if (!game->monsters[order[i]].alive)
		{
			i++;
			continue ;
		}
		sprite = calc_sprite_pos(game, order, i, &sprite);
		process_monster_sprite(game, &sprite, order[i]);
		i++;
	}
}
