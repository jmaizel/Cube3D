/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:31:16 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/27 17:50:49 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Initialise les monstres dans la map */
void	init_monsters(t_game *game)
{
	int x, y;
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
				{
					ft_printf("Warning: Monstre trouvé mais pas de texture d'animation\n");
				}
				game->monsters[game->monster_count].x = x + 0.5;
				game->monsters[game->monster_count].y = y + 0.5;
				game->monsters[game->monster_count].alive = 1;
				// Initialiser les paramètres d'animation
				game->monsters[game->monster_count].frame = 0;
				game->monsters[game->monster_count].anim_time = 0.0;
				game->monsters[game->monster_count].anim_speed = 0.2;
					// 5 frames par seconde
				game->monsters[game->monster_count].health = 100;
				game->monsters[game->monster_count].max_health = 100;
				game->monsters[game->monster_count].hit_animation = 0;
				game->monsters[game->monster_count].hit_timer = 0.0;
				game->monster_count++;
				game->map.grid[y][x] = '0'; // Remplacer par un espace vide
			}
			x++;
		}
		y++;
	}
}

/* Trie les monstres par distance pour le rendu */
void	sort_monsters(t_game *game, double *distances, int *order)
{
	int		i;
	int		j;
	int		tmp;
	double	tmp_dist;

	i = 0;
	while (i < game->monster_count)
	{
		order[i] = i;
		distances[i] = ((game->player.x - game->monsters[i].x) * (game->player.x
					- game->monsters[i].x) + (game->player.y
					- game->monsters[i].y) * (game->player.y
					- game->monsters[i].y));
		i++;
	}
	i = 0;
	while (i < game->monster_count - 1)
	{
		j = 0;
		while (j < game->monster_count - i - 1)
		{
			if (distances[j] < distances[j + 1])
			{
				tmp_dist = distances[j];
				distances[j] = distances[j + 1];
				distances[j + 1] = tmp_dist;
				tmp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/* Dessine un monstre avec transparence */
void draw_monster_column(t_game *game, int stripe, int draw_start_y,
	int draw_end_y, t_sprite *sprite, int tex_x, int monster_index)
{
int     y;
int     d;
int     tex_y;
int     color;
int     frame;

// Utiliser la frame actuelle du monstre
frame = game->monsters[monster_index].frame;
if (frame >= game->monster_frame_count)
	frame = 0;

y = draw_start_y;
while (y < draw_end_y)
{
	d = (y)*256 - WIN_HEIGHT * 128 + sprite->height * 128;
	tex_y = ((d * game->monster_frames[frame].height) / sprite->height) / 256;
	if (tex_y >= 0 && tex_y < game->monster_frames[frame].height && tex_x >= 0
		&& tex_x < game->monster_frames[frame].width)
	{
		color = game->monster_frames[frame].data[game->monster_frames[frame].width * tex_y
			+ tex_x];

		if ((color & 0x00FFFFFF) != 0x000000)
		{
			if (game->monsters[monster_index].hit_animation)
			{
				int red = (color >> 16) & 0xFF;
                red = fmin(255, red + 100);
  
                color = (red << 16) | (color & 0x00FFFF);
			}
			
			game->img_data[y * (game->size_line / 4) + stripe] = color;
		}
	}
	y++;
}
}

void	render_monsters(t_game *game)
{
	int			i;
	int			order[MAX_MONSTERS];
	double		distances[MAX_MONSTERS];
	t_sprite	sprite;
	int			stripe;
	int			tex_x;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;

	// Si pas de frames d'animation, on sort
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
		sprite.x = game->monsters[order[i]].x - game->player.x;
		sprite.y = game->monsters[order[i]].y - game->player.y;
		inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
				- game->player.dir_x * game->player.plane_y);
		transform_x = inv_det * (game->player.dir_y * sprite.x
				- game->player.dir_x * sprite.y);
		transform_y = inv_det * (-game->player.plane_y * sprite.x
				+ game->player.plane_x * sprite.y);
		sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x
					/ transform_y));
		sprite.height = abs((int)(WIN_HEIGHT / transform_y));
		sprite.width = sprite.height;
		draw_start_y = -sprite.height / 2 + WIN_HEIGHT / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		draw_end_y = sprite.height / 2 + WIN_HEIGHT / 2;
		if (draw_end_y >= WIN_HEIGHT)
			draw_end_y = WIN_HEIGHT - 1;
		draw_start_x = -sprite.width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = sprite.width / 2 + sprite_screen_x;
		if (draw_end_x >= WIN_WIDTH)
			draw_end_x = WIN_WIDTH - 1;
		stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			tex_x = (int)(256 * (stripe - (-sprite.width / 2 + sprite_screen_x))
					* game->monster_frames[0].width / sprite.width) / 256;
			if (transform_y > 0 && stripe > 0 && stripe < WIN_WIDTH
				&& transform_y < game->z_buffer[stripe])
			{
				draw_monster_column(game, stripe, draw_start_y, draw_end_y,
					&sprite, tex_x, order[i]);
			}
			stripe++;
		}
		i++;
	}
}

int all_monsters_dead(t_game *game)
{
    int i;
    
    for (i = 0; i < game->monster_count; i++)
    {
        if (game->monsters[i].alive)
            return (0);  // Au moins un monstre est encore en vie
    }
    
    return (1);  // Tous les monstres sont morts
}