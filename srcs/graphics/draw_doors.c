/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:50:12 by cdedessu          #+#    #+#             */
/*   Updated: 2025/04/27 17:51:07 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_special_door(t_game *game)
{
    int x, y;
    
    game->has_special_door = 0;
    game->special_door_open = 0;
    
    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < (int)ft_strlen(game->map.grid[y]))
        {
            if (game->map.grid[y][x] == 'L')  // 'L' pour porte verrouillée
            {
                if (game->has_special_door)
                {
                    ft_printf("Warning: Multiple special doors found, only using the first one.\n");
                    continue;
                }
                
                if (!game->special_door_path)
                {
                    ft_printf("Warning: Special door found but no SD texture specified.\n");
                    continue;
                }
                
                game->has_special_door = 1;
                game->special_door_x = x;
                game->special_door_y = y;
                game->special_door_open = 0;  // Fermée par défaut
            }
            x++;
        }
        y++;
    }
}

void update_special_door(t_game *game)
{
    if (!game->has_special_door || game->special_door_open)
        return;
    
    if (all_monsters_dead(game))
    {
        game->special_door_open = 1;
        ft_printf("La porte verrouillée s'est ouverte!\n");
    }
}

void check_special_door_interaction(t_game *game)
{
    int check_x, check_y;
    
    // Position devant le joueur
    check_x = (int)(game->player.x + game->player.dir_x);
    check_y = (int)(game->player.y + game->player.dir_y);
    
    // Vérifier si c'est la porte spéciale
    if (game->has_special_door && check_x == game->special_door_x && check_y == game->special_door_y)
    {
        if (game->special_door_open)
            ft_printf("La porte est déjà ouverte.\n");
        else if (all_monsters_dead(game))
        {
            game->special_door_open = 1;
            ft_printf("La porte s'ouvre!\n");
        }
        else
            ft_printf("Cette porte semble verrouillée. Peut-être que l'élimination de tous les ennemis la débloquera?\n");
    }
}