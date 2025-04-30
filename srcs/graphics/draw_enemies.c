/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:31:16 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 17:27:46 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Initialise les monstres dans la map
 * Recherche les positions 'M' dans la grille et crée des monstres à ces endroits
 * 
 * @param game Structure principale du jeu
 */
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
				game->monsters[game->monster_count].x = x + 0.5;
				game->monsters[game->monster_count].y = y + 0.5;
				game->monsters[game->monster_count].alive = 1;
				game->monsters[game->monster_count].frame = 0;
				game->monsters[game->monster_count].anim_time = 0.0;
				game->monsters[game->monster_count].anim_speed = 0.2;
				game->monsters[game->monster_count].health = 100;
				game->monsters[game->monster_count].max_health = 100;
				game->monsters[game->monster_count].hit_animation = 0;
				game->monsters[game->monster_count].hit_timer = 0.0;
				game->monster_count++;
				game->map.grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

/**
 * Dessine tous les monstres à l'écran
 * 
 * @param game Structure principale du jeu
 */
void	render_monsters(t_game *game)
{
	int			i;
	int			order[MAX_MONSTERS];
	double		distances[MAX_MONSTERS];
	t_sprite	sprite;
	int			stripe;
	int			tex_x;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;

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
		calc_sprite_draw_limits(&sprite, &draw_start_x, &draw_end_x,
			&draw_start_y, &draw_end_y);
		stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			tex_x = (int)(256 * (stripe - (-sprite.width / 2 + sprite.screen_x))
					* game->monster_frames[0].width / sprite.width) / 256;
			if (sprite.transform_y > 0 && stripe > 0 && stripe < WIN_WIDTH
				&& sprite.transform_y < game->z_buffer[stripe])
				draw_monster_column(game, stripe, draw_start_y, draw_end_y,
					&sprite, tex_x, order[i]);
			stripe++;
		}
		i++;
	}
}

/**
 * Vérifie si tous les monstres sont morts
 * 
 * @param game Structure principale du jeu
 * @return 1 si tous les monstres sont morts, 0 sinon
 */
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
