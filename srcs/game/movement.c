/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:45:10 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/27 17:53:26 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

/* Vérifie si une position sur la map est valide (pas de mur ni hors limites) */
int	is_valid_position(t_game *game, double x, double y)
{
	if (x < 0 || y < 0 || (int)x >= game->map.width
		|| (int)y >= game->map.height)
		return (0);
	if (game->map.grid[(int)y][(int)x] == '1')
		return (0);
	return (1);
}

/* Déplace le joueur vers l'avant */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * game->move_speed;
	new_y = game->player.y + game->player.dir_y * game->move_speed;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Déplace le joueur vers l'arrière */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Déplace le joueur vers la gauche */
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Déplace le joueur vers la droite */
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Fait pivoter le joueur vers la gauche */
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED)
		- game->player.dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y
		* cos(-ROT_SPEED);
	game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED)
		- game->player.plane_y * sin(-ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y
		* cos(-ROT_SPEED);
}

/* Fait pivoter le joueur vers la droite */
void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(ROT_SPEED)
		- game->player.dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y
		* cos(ROT_SPEED);
	game->player.plane_x = game->player.plane_x * cos(ROT_SPEED)
		- game->player.plane_y * sin(ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y
		* cos(ROT_SPEED);
}

/* Gère l'appui sur une touche */
int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 1;
	if (keycode == 65361 || keycode == 123) // Flèche gauche
		game->rotate_left = 1;
	else if (keycode == 65363 || keycode == 124) // Flèche droite
		game->rotate_right = 1;
	else if (keycode == 65307 || keycode == 53) // ESC key
		close_window(game);
	else if (keycode == 109 || keycode == 46) // Touche M
		toggle_mouse(game);
	else if (keycode == 32 || keycode == 1) // Touche espace ou clic gauche
		attack(game);
	else if (keycode == 101 || keycode == 14) // Touche E pour interaction
        check_special_door_interaction(game);
		
	return (0);
}

/* Gère le relâchement d'une touche */
int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 0;
	if (keycode == 65361 || keycode == 123)
		game->rotate_left = 0;
	else if (keycode == 65363 || keycode == 124)
		game->rotate_right = 0;
	return (0);
}

/* Gère tous les mouvements actifs du joueur */
void	handle_movement(t_game *game)
{
	if (game->keys[119] || game->keys[13])
		move_forward(game);
	if (game->keys[115] || game->keys[1])
		move_backward(game);
	if (game->keys[97] || game->keys[0])
		move_left(game);
	if (game->keys[100] || game->keys[2])
		move_right(game);
	if (game->rotate_left)
		rotate_left(game);
	if (game->rotate_right)
		rotate_right(game);
}
double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void	update_monster_animations(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->monster_count)
	{
		if (game->monsters[i].alive)
		{
			// Ajouter le temps écoulé
			game->monsters[i].anim_time += game->delta_time;
				// Utilise game->delta_time
			// Changer de frame si nécessaire
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

/* boucle principale du jeu */
int	game_loop(t_game *game)
{
	double current_time;

	// Calculer le delta time
	current_time = get_time();
	if (game->last_frame_time == 0.0)
		game->last_frame_time = current_time;

	game->delta_time = current_time - game->last_frame_time;
	game->last_frame_time = current_time;

	// Limiter le delta time pour éviter les sauts lors de freezes
	if (game->delta_time > 0.1)
		game->delta_time = 0.1;

	// Mettre à jour le timer de l'arme
	if (game->weapon_timer > 0)
	{
		game->weapon_timer -= game->delta_time;
		if (game->weapon_timer <= 0)
		{
			game->weapon_timer = 0;
			game->firing = 0;
		}
	}

	// Mettre à jour l'animation de l'arme
	if (game->weapon_animating)
	{
		game->weapon_anim_time += game->delta_time;

		// Avancer l'animation
		if (game->weapon_anim_time >= game->weapon_anim_speed)
		{
			game->weapon_anim_time -= game->weapon_anim_speed;
			game->current_weapon_frame++;

			// Vérifier si l'animation est terminée
			if (game->current_weapon_frame >= game->weapon_frame_count)
			{
				game->current_weapon_frame = 0;
				game->weapon_animating = 0;
			}
		}
	}

	// Mettre à jour les effets de coup pour les monstres
	for (int i = 0; i < game->monster_count; i++)
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
	}

	// Vérifier si tous les monstres sont morts pour les portes spéciales
	update_special_door(game);

	// Mise à jour des animations des monstres
	update_monster_animations(game);

	// Gérer les mouvements du joueur
	handle_movement(game);

	// Générer la nouvelle frame
	render_frame(game);

	// Afficher la frame
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

	// Limiter le framerate à environ 60 FPS
	usleep(16000);

	return (0);
}