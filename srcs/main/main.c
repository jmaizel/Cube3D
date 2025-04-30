/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:37:18 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:15:53 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Initialise les valeurs de la structure de jeu */
void	init_game_values(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->rotate_left = 0;
	game->rotate_right = 0;
	game->move_speed = 0.13;
	game->rot_speed = 0.03;
	game->monster_frame_count = 0;
	game->last_frame_time = 0.0;
	game->delta_time = 0.0;
	game->mouse_enabled = 0;
	game->mouse_sensitivity = 0.002;
	game->mouse_x = WIN_WIDTH / 2;
	game->mouse_prev_x = WIN_WIDTH / 2;
}

/* Initialise les paramètres liés aux armes */
void	init_weapon_values(t_game *game)
{
	game->firing = 0;
	game->weapon_cooldown = 0.5;
	game->weapon_timer = 0.0;
	game->weapon_damage = 25;
	game->weapon_range = 3.0;
	game->weapon_frame_count = 0;
	game->current_weapon_frame = 0;
	game->weapon_animating = 0;
	game->weapon_anim_time = 0;
	game->weapon_anim_speed = 0.1;
}

/* Initialise les flags pour l'état du jeu */
void	init_game_state(t_game *game)
{
	game->door_opened = 0;
	game->all_monsters_killed = 0;
	game->victory_displayed = 0;
	game->victory_timer = 0.0;
	game->victory_final = 0;
}

/* Configure les hooks de la MLX */
void	setup_mlx_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook(game->win, mouse_click, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

/* Point d'entrée principal du programme */
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (exit_error("Usage: ./cub3D map.cub"), 1);
	init_game_values(&game);
	init_weapon_values(&game);
	init_game_state(&game);
	if (!parse_cub_file(argv[1], &game))
		return (1);
	init_monsters(&game);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (exit_error("Erreur init MLX"), 1);
	if (!load_all_textures(&game))
		return (1);
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D avec raycasting");
	if (!game.win)
		return (exit_error("Erreur fenêtre"), 1);
	game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	game.img_data = (int *)mlx_get_data_addr(game.img, &game.bpp,
			&game.size_line, &game.endian);
	render_frame(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	setup_mlx_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}