/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:37:18 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/22 13:34:08 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_game_part_two(t_game *game)
{
	game->weapon_damage = 25;
	game->weapon_range = 2.0;
	game->weapon_frame_count = 0;
	game->current_weapon_frame = 0;
	game->weapon_animating = 0;
	game->weapon_anim_time = 0;
	game->weapon_anim_speed = 0.1;
	game->door_opened = 0;
	game->all_monsters_killed = 0;
	game->victory_displayed = 0;
	game->victory_timer = 0.0;
	game->victory_final = 0;
	game->victory_tex.img = NULL;
}

static void	init_game_structure(t_game *game)
{
	int	i;

	ft_memset(game, 0, sizeof(t_game));
	i = 0;
	while (i < 4)
	{
		game->weapon_paths[i] = NULL;
		game->monster_paths[i] = NULL;
		i++;
	}
	game->rotate_left = 0;
	game->rotate_right = 0;
	game->move_speed = 0.13;
	game->rot_speed = 0.03;
	game->monster_frame_count = 0;
	game->last_frame_time = 0.0;
	game->delta_time = 0.0;
	game->firing = 0;
	game->weapon_cooldown = 0.5;
	game->weapon_timer = 0.0;
	init_game_part_two(game);
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

static int	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (exit_error("Erreur init MLX"), 0);
	if (!load_all_textures(game))
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
		return (0);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D avec raycasting");
	if (!game->win)
	{
		cleanup_texture_resources(game);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
		return (exit_error("Erreur fenêtre"), 0);
	}
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
	{
		mlx_destroy_window(game->mlx, game->win);
		cleanup_texture_resources(game);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
		return (exit_error("Erreur image"), 0);
	}
	game->img_data = (int *)mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (exit_error("Usage: ./cub3D map.cub"), 1);
	init_game_structure(&game);
	if (!parse_cub_file(argv[1], &game))
	{
		// Le nettoyage est déjà fait dans parse_cub_file
		return (1);
	}
	init_monsters(&game);
	if (!init_graphics(&game))
	{
		if (game.map.grid)
			free_map(game.map.grid);
		cleanup_config_resources(&game);
		return (1);
	}
	render_frame(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
