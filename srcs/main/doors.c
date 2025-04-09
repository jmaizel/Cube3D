/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:04:32 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/09 15:05:06 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_door_interaction(t_game *game)
{
    int check_x, check_y;
    
    // Vérifier devant le joueur
    check_x = (int)(game->player.x + game->player.dir_x);
    check_y = (int)(game->player.y + game->player.dir_y);
    
    if (check_x >= 0 && check_y >= 0 && check_y < game->map.height && 
        check_x < (int)ft_strlen(game->map.grid[check_y]) &&
        game->map.grid[check_y][check_x] == 'P')
    {
        return (1);
    }
    return (0);
}

void init_doors(t_game *game)
{
    int x, y;
    
    game->door_count = 0;
    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < (int)ft_strlen(game->map.grid[y]))
        {
            if (game->map.grid[y][x] == 'P')
            {
                game->door_positions[game->door_count][0] = x;
                game->door_positions[game->door_count][1] = y;
                game->door_state[game->door_count] = 0; // Fermée par défaut
                game->door_count++;
            }
            x++;
        }
        y++;
    }
}