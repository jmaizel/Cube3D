/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:37:18 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/25 13:23:09 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Ferme la fenêtre et libère toutes les ressources allouées */
int	close_window(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free_map(game->map.grid);
	exit(0);
	return (0);
}

/* Trouve l'index d'une porte à partir de ses coordonnées */
int	get_door_index(t_game *game, int x, int y)
{
	for (int i = 0; i < game->door_count; i++)
	{
		if (game->door_positions[i][0] == x && game->door_positions[i][1] == y)
			return (i);
	}
	return (-1);
}

/* Point d'entrée principal du programme */
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (exit_error("Usage: ./cub3D map.cub"), 1);
	ft_memset(&game, 0, sizeof(t_game));
	game.rotate_left = 0;
	game.rotate_right = 0;
	game.move_speed = 0.13;
	game.rot_speed = 0.03;
	game.door_count = 0;
	if (!parse_cub_file(argv[1], &game))
		return (1);
	init_doors(&game);
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
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}