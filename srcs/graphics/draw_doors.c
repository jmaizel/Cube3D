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
            if (game->map.grid[y][x] == 'D')  // 'D' pour door normale
            {
                if (!game->door_path)
                    return (exit_error("Error\nPorte trouvée mais pas de texture DO"), (void)0);
                
                game->door_positions[game->door_count][0] = x;
                game->door_positions[game->door_count][1] = y;
                game->door_state[game->door_count] = 0;  // Fermée par défaut
                game->door_count++;
            }
            else if (game->map.grid[y][x] == 'L')  // 'L' pour porte spéciale (locked)
            {
                if (!game->special_door_path)
                    return (exit_error("Error\nPorte spéciale trouvée mais pas de texture SD"), (void)0);
                
                game->special_door_positions[game->special_door_count][0] = x;
                game->special_door_positions[game->special_door_count][1] = y;
                game->special_door_state[game->special_door_count] = 0;  // Fermée par défaut
                game->special_door_count++;
            }
            x++;
        }
        y++;
    }
}

int check_door_interaction(t_game *game)
{
    int check_x, check_y;
    int i;
    
    // Position devant le joueur
    check_x = (int)(game->player.x + game->player.dir_x);
    check_y = (int)(game->player.y + game->player.dir_y);
    
    // Vérifier les portes normales
    for (i = 0; i < game->door_count; i++)
    {
        if (game->door_positions[i][0] == check_x && 
            game->door_positions[i][1] == check_y && 
            game->door_state[i] == 0)  // Si la porte est fermée
        {
            // Ouvrir la porte
            game->door_state[i] = 1;
            ft_printf("Porte ouverte!\n");
            return (1);
        }
    }
    
    return (0);
}

int get_door_index(t_game *game, int x, int y)
{
    int i;
    
    for (i = 0; i < game->door_count; i++)
    {
        if (game->door_positions[i][0] == x && game->door_positions[i][1] == y)
            return (i);
    }
    
    return (-1);
}

int get_special_door_index(t_game *game, int x, int y)
{
    int i;
    
    for (i = 0; i < game->special_door_count; i++)
    {
        if (game->special_door_positions[i][0] == x && game->special_door_positions[i][1] == y)
            return (i);
    }
    
    return (-1);
}

void update_special_doors(t_game *game)
{
    int i;
    
    if (all_monsters_dead(game) && game->special_door_count > 0)
    {
        for (i = 0; i < game->special_door_count; i++)
        {
            if (game->special_door_state[i] == 0)  // Si la porte est fermée
            {
                game->special_door_state[i] = 1;  // Ouvrir la porte
                ft_printf("Une porte spéciale s'est ouverte!\n");
            }
        }
    }
}