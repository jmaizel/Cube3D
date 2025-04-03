/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:37:18 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/03 10:46:57 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	complete_raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		init_ray(&ray, game, x);
		calculate_step_and_side_dist(&ray);
		safe_perform_dda(&ray, game);
		calculate_line_height(&ray);
		draw_textured_line(x, &ray, game);
		x++;
	}
}

void	render_frame(t_game *game)
{
	int x, y;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				game->img_data[y * (game->size_line / 4)
					+ x] = game->ceiling_color;
			else
				game->img_data[y * (game->size_line / 4)
					+ x] = game->floor_color;
			x++;
		}
		y++;
	}
	complete_raycasting(game);
	draw_minimap(game);
	draw_gun(game);
}

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

void	safe_perform_dda(t_ray *ray, t_game *game)
{
	int	max_iterations;
	int	iterations;

	max_iterations = 100;
	iterations = 0;
	while (ray->hit == 0 && iterations < max_iterations)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= game->map.height || ray->map_x < 0)
		{
			ray->hit = 1;
		}
		else if (ray->map_x >= (int)ft_strlen(game->map.grid[ray->map_y]))
		{
			ray->hit = 1;
		}
		else if (game->map.grid[ray->map_y][ray->map_x] == '1')
		{
			ray->hit = 1;
		}
		iterations++;
	}
}

void	safe_draw_textured_line(int x, t_ray *ray, t_game *game)
{
	int	color;
	int	y;

	color = 0;
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			color = 0xFF0000;
		else
			color = 0x00FF00;
	}
	else
	{
		if (ray->dir_y > 0)
			color = 0x0000FF;
		else
			color = 0xFFFF00;
	}
	if (ray->side == 1)
		color = (color >> 1) & 0x7F7F7F;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		if (y >= 0 && y < WIN_HEIGHT && x >= 0 && x < WIN_WIDTH)
			game->img_data[y * (game->size_line / 4) + x] = color;
		y++;
	}
}
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (exit_error("Usage: ./cub3D map.cub"), 1);
	ft_memset(&game, 0, sizeof(t_game));
	if (!parse_cub_file(argv[1], &game))
		return (1);
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
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
