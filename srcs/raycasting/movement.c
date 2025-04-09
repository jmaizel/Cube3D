/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:45:10 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/09 14:56:07 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

int	is_valid_position(t_game *game, double x, double y)
{
	if (x < 0 || y < 0 || (int)x >= game->map.width
		|| (int)y >= game->map.height)
		return (0);
	if (game->map.grid[(int)y][(int)x] == '1')
		return (0);
	return (1);
}

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
int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 1;
	// Gestion spécifique des touches flèches
	if (keycode == 65361 || keycode == 123) // Flèche gauche
		game->rotate_left = 1;
	// Nouvelle variable dans t_game
	else if (keycode == 65363 || keycode == 124) // Flèche droite
		game->rotate_right = 1;
	// Nouvelle variable dans t_game
	else if (keycode == 65307 || keycode == 53) // ESC key
		close_window(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 0;
	// Gestion spécifique des touches flèches
	if (keycode == 65361 || keycode == 123) // Flèche gauche
		game->rotate_left = 0;
	else if (keycode == 65363 || keycode == 124) // Flèche droite
		game->rotate_right = 0;
	return (0);
}

void	handle_movement(t_game *game)
{
	// Mouvements avant/arrière (W/S)
	if (game->keys[119] || game->keys[13]) // W
		move_forward(game);
	if (game->keys[115] || game->keys[1]) // S
		move_backward(game);
	// Mouvements latéraux (A/D)
	if (game->keys[97] || game->keys[0]) // A
		move_left(game);
	if (game->keys[100] || game->keys[2]) // D
		move_right(game);
	// Rotations (flèches gauche/droite)
	if (game->rotate_left)
		rotate_left(game);
	if (game->rotate_right)
		rotate_right(game);
}

int	game_loop(t_game *game)
{
	// Traiter tous les mouvements actifs
	handle_movement(game);

	// Mettre à jour l'image
	render_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

	// Petit délai pour ralentir la boucle (en millisecondes)
	usleep(16000); // Environ 60 FPS (1000ms/60 ≈ 16.7ms)

	return (0);
}