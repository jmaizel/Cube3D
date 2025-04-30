/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:00 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:31:31 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Met à jour le temps et les timers du jeu */
void	update_game_timers(t_game *game)
{
	double	current_time;
	int		i;

	current_time = get_time();
	if (game->last_frame_time == 0.0)
		game->last_frame_time = current_time;
	game->delta_time = current_time - game->last_frame_time;
	game->last_frame_time = current_time;
	if (game->delta_time > 0.1)
		game->delta_time = 0.1;
	if (game->weapon_timer > 0)
	{
		game->weapon_timer -= game->delta_time;
		if (game->weapon_timer <= 0)
		{
			game->weapon_timer = 0;
			game->firing = 0;
		}
	}
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

/* Met à jour l'animation de l'arme */
void	update_weapon_animation(t_game *game)
{
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

/* Vérifie si le joueur est proche de la porte */
int	check_door_proximity(t_game *game, int door_x, int door_y)
{
	double	dx;
	double	dy;
	double	distance;

	dx = game->player.x - (door_x + 0.5);
	dy = game->player.y - (door_y + 0.5);
	distance = sqrt(dx * dx + dy * dy);
	return (distance < 1.0);
}

/* Affiche le message de victoire et termine le jeu */
void	display_victory_and_exit(t_game *game)
{
	int	msg_x;
	int	msg_y;

	ft_printf("VICTOIRE! Vous avez traversé la porte et terminé le jeu!\n");
	game->victory_displayed = 2;
	render_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	msg_x = WIN_WIDTH / 2 - 200;
	msg_y = WIN_HEIGHT / 2;
	mlx_string_put(game->mlx, game->win, msg_x, msg_y - 40, 0xFFFF00,
		"FÉLICITATIONS!");
	mlx_string_put(game->mlx, game->win, msg_x, msg_y, 0xFFFF00,
		"VOUS AVEZ TERMINÉ LE JEU!");
	usleep(2000000);
	close_window(game);
}

/* Met à jour le timer de victoire */
void	update_victory_timer(t_game *game)
{
	if (game->victory_timer > 0)
	{
		game->victory_timer -= game->delta_time;
		if (game->victory_timer <= 0)
		{
			game->victory_timer = 0;
			if (game->victory_displayed == 1)
				game->victory_displayed = 0;
		}
	}
}

/* Boucle principale du jeu */
int	game_loop(t_game *game)
{
	update_game_timers(game);
	update_weapon_animation(game);
	update_monster_animations(game);
	
	// Vérifier si les monstres sont morts et mettre à jour l'état
	if (!game->all_monsters_killed && all_monsters_dead(game))
	{
		game->all_monsters_killed = 1;
		game->door_opened = 1;
		game->victory_timer = 3.0;
		game->victory_displayed = 1;
		ft_printf("Tous les monstres ont été éliminés! La porte est ouverte!\n");
	}
	
	// Vérifier la victoire
	if (game->door_opened && game->victory_displayed != 2)
	{
		int door_x, door_y;
		if (find_door_position(game, &door_x, &door_y))
		{
			if (check_door_proximity(game, door_x, door_y))
			{
				display_victory_and_exit(game);
			}
		}
	}
	
	update_victory_timer(game);
	handle_movement(game);
	render_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	if (game->victory_displayed || game->all_monsters_killed)
		draw_victory_message(game);
	usleep(16000);
	return (0);
}