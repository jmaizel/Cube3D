/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:45:10 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 17:08:16 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

/**
 * Vérifie si une position est valide (pas de collision avec un mur)
 * 
 * @param game Structure principale du jeu
 * @param x Position x à vérifier
 * @param y Position y à vérifier
 * @return 1 si la position est valide, 0 sinon
 */
int	is_valid_position(t_game *game, double x, double y)
{
	if (x < 0 || y < 0 || (int)x >= game->map.width
		|| (int)y >= game->map.height)
		return (0);
	if (game->map.grid[(int)y][(int)x] == '1')
		return (0);
	if (game->map.grid[(int)y][(int)x] == 'D' && !game->door_opened)
		return (0);
	return (1);
}

/**
 * Déplace le joueur vers l'avant
 * 
 * @param game Structure principale du jeu
 */
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

/**
 * Déplace le joueur vers l'arrière
 * 
 * @param game Structure principale du jeu
 */
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

/**
 * Déplace le joueur vers la gauche
 * 
 * @param game Structure principale du jeu
 */
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

/**
 * Déplace le joueur vers la droite
 * 
 * @param game Structure principale du jeu
 */
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

/**
 * Fait pivoter le joueur vers la gauche
 * 
 * @param game Structure principale du jeu
 */
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

/**
 * Fait pivoter le joueur vers la droite
 * 
 * @param game Structure principale du jeu
 */
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

/**
 * Gère l'appui sur une touche
 * 
 * @param keycode Code de la touche appuyée
 * @param game Structure principale du jeu
 * @return 0 (toujours réussi)
 */
int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 1;
	if (keycode == 65361 || keycode == 123)
		game->rotate_left = 1;
	else if (keycode == 65363 || keycode == 124)
		game->rotate_right = 1;
	else if (keycode == 65307 || keycode == 53)
		close_window(game);
	else if (keycode == 109 || keycode == 46)
		toggle_mouse(game);
	else if (keycode == 32 || keycode == 1)
		attack(game);
	return (0);
}

/**
 * Gère le relâchement d'une touche
 * 
 * @param keycode Code de la touche relâchée
 * @param game Structure principale du jeu
 * @return 0 (toujours réussi)
 */
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

/**
 * Gère tous les mouvements actifs du joueur
 * 
 * @param game Structure principale du jeu
 */
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

/**
 * Boucle principale du jeu qui gère les updates et le rendu
 * 
 * @param game Structure principale du jeu
 * @return 0 (toujours réussi) ou résultat de display_victory
 */
int	game_loop(t_game *game)
{
	int	victory_result;

	calculate_delta_time(game);
	update_weapon_timer(game);
	update_monster_hit_effects(game);
	update_monster_animations(game);
	check_monsters_status(game);
	victory_result = check_door_victory(game);
	if (victory_result != 0)
		return (victory_result);
	update_victory_timer(game);
	handle_movement(game);
	render_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	draw_controls_menu(game);
	usleep(16000);
	return (0);
}
