/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:16:22 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/02 19:37:18 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Vérifie si un monstre est à portée d'attaque
 */
static int	is_monster_in_range(t_game *game, int monster_index)
{
	double	dx;
	double	dy;
	double	distance;

	if (!game->monsters[monster_index].alive)
		return (0);
	dx = game->monsters[monster_index].x - game->player.x;
	dy = game->monsters[monster_index].y - game->player.y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > game->weapon_range)
		return (0);
	return (is_monster_in_fov(game, dx, dy));
}

/**
 * Attaque un monstre spécifique si à portée
 */
static void	attack_monster(t_game *game, int monster_index)
{
	if (is_monster_in_range(game, monster_index))
		damage_monster(game, monster_index);
}

/**
 * Gère l'attaque du joueur contre les monstres
 */
void	attack(t_game *game)
{
	int	i;

	if (game->weapon_timer > 0)
		return ;
	init_weapon_animation(game);
	i = 0;
	while (i < game->monster_count)
	{
		attack_monster(game, i);
		i++;
	}
}
