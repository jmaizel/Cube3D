/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:34:40 by cdedessu          #+#    #+#             */
/*   Updated: 2025/04/28 17:43:25 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_controls_menu(t_game *game)
{
    int x_start = WIN_WIDTH - 300;
    int y_start = 20;
    int line_height = 20;
    int i = 0;
    
    int title_color = 0xFFFF00;
    int key_color = 0x00FFFF;
    int action_color = 0xFFFFFF;
    
    mlx_string_put(game->mlx, game->win, x_start, y_start + line_height * i++, title_color, "CONTROLS:");
    
    mlx_string_put(game->mlx, game->win, x_start, y_start + line_height * i, key_color, "WASD:");
    mlx_string_put(game->mlx, game->win, x_start + 60, y_start + line_height * i++, action_color, "Move");
    
    mlx_string_put(game->mlx, game->win, x_start, y_start + line_height * i, key_color, "Arrows/Mouse:");
    mlx_string_put(game->mlx, game->win, x_start + 120, y_start + line_height * i++, action_color, "Look");
    
    mlx_string_put(game->mlx, game->win, x_start, y_start + line_height * i, key_color, "M:");
    mlx_string_put(game->mlx, game->win, x_start + 30, y_start + line_height * i++, action_color, "Toggle mouse");
    
    mlx_string_put(game->mlx, game->win, x_start, y_start + line_height * i, key_color, "LMB/Space:");
    mlx_string_put(game->mlx, game->win, x_start + 100, y_start + line_height * i++, action_color, "Shoot");
    
    mlx_string_put(game->mlx, game->win, x_start, y_start + line_height * i, key_color, "ESC:");
    mlx_string_put(game->mlx, game->win, x_start + 50, y_start + line_height * i++, action_color, "Quit");
}
