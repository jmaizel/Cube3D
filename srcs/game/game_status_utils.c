/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_status_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:18:06 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 11:01:09 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_monsters_status(t_game *game)
{
	if (!game->all_monsters_killed && all_monsters_dead(game))
	{
		game->all_monsters_killed = 1;
		game->door_opened = 1;
		game->victory_timer = 3.0;
		game->victory_displayed = 1;
		ft_printf("All monsters are eliminated ! \n");
		ft_printf("The door is open ! \n");
	}
}

int	find_door_position(t_game *game, int *door_x, int *door_y)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == 'D')
			{
				*door_x = x;
				*door_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	display_victory(t_game *game)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;

	ft_printf("You've gone through the door and finished the game!\n");
	game->victory_displayed = 2;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			game->img_data[y * (game->size_line / 4) + x] = 0x000000;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	if (game->victory_tex.img)
	{
		start_x = (WIN_WIDTH - game->victory_tex.width) / 2;
		start_y = (WIN_HEIGHT - game->victory_tex.height) / 2;
		mlx_put_image_to_window(game->mlx, game->win, game->victory_tex.img,
			start_x, start_y);
	}
	ft_printf("Victory screen displayed. Press ESC to exit.\n");
	return (0);
}

int	check_door_victory(t_game *game)
{
	int		door_x;
	int		door_y;
	double	dx;
	double	dy;
	double	distance;

	if (!game->door_opened || game->victory_displayed == 2)
		return (0);
	if (!find_door_position(game, &door_x, &door_y))
		return (0);
	dx = game->player.x - (door_x + 0.5);
	dy = game->player.y - (door_y + 0.5);
	distance = sqrt(dx * dx + dy * dy);
	if (distance < 1.0)
	{
		display_victory(game);
		return (0);
	}
	return (0);
}

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
