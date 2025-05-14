/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:34:40 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:40:30 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_control_item(t_game *game, int pos_y, char *key_str,
		char *action_str)
{
	int	x_start;
	int	key_color;
	int	action_color;
	int	key_len;

	x_start = WIN_WIDTH - 300;
	key_color = 0x00FFFF;
	action_color = 0xFFFFFF;
	key_len = ft_strlen(key_str) * 6;
	mlx_string_put(game->mlx, game->win, x_start, pos_y, key_color, key_str);
	mlx_string_put(game->mlx, game->win, x_start + key_len, pos_y,
		action_color, action_str);
}

void	draw_controls_menu(t_game *game)
{
	int	x_start;
	int	y_start;
	int	line_height;
	int	i;
	int	title_color;

	x_start = WIN_WIDTH - 300;
	y_start = 20;
	line_height = 20;
	i = 0;
	title_color = 0xFFFF00;
	mlx_string_put(game->mlx, game->win, x_start, y_start + line_height * i++,
		title_color, "CONTROLS:");
	draw_control_item(game, y_start + line_height * i++, "WASD:", "Move");
	draw_control_item(game, y_start + line_height * i++, "Arrows/Mouse:",
		"Look");
	draw_control_item(game, y_start + line_height * i++, "M:",
		"Toggle mouse");
	draw_control_item(game, y_start + line_height * i++, "LMB/Space:",
		"Shoot");
	draw_control_item(game, y_start + line_height * i++, "ESC:", "Quit");
}
