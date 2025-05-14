/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:36:14 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:34:23 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 1;
	if (game->victory_displayed == 2)
	{
		if (keycode == 65307 || keycode == 53)
			close_window(game);
		return (0);
	}
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
