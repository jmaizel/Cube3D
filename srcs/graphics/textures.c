/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:22:34 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/22 15:46:55 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_texture(t_ray *ray, t_game *game, t_texture **tex)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			*tex = &game->east_tex;
		else
			*tex = &game->west_tex;
	}
	else
	{
		if (ray->dir_y > 0)
			*tex = &game->south_tex;
		else
			*tex = &game->north_tex;
	}
}

void	calculate_texture_x(t_ray *ray, double *wall_x, int *tex_x,
		t_texture *tex)
{
	if (ray->side == 0)
		*wall_x = ray->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		*wall_x = ray->pos_x + ray->perp_wall_dist * ray->dir_x;
	*wall_x -= floor(*wall_x);
	*tex_x = (int)(*wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1
			&& ray->dir_y > 0))
		*tex_x = tex->width - *tex_x - 1;
}

static char	*ft_trim_path(char *path)
{
	char	*start;
	char	*end;
	char	*trimmed;
	int		len;
	int		i;

	start = path;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	len = end - start + 1;
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	i = 0;
	while (i < len)
	{
		trimmed[i] = start[i];
		i++;
	}
	trimmed[len] = '\0';
	return (trimmed);
}

int	load_texture(t_game *game, t_texture *texture, char *path)
{
	char	*original_path;
	char	*trimmed_path;
	void	*img_ptr;

	original_path = (char *)texture->img;
	trimmed_path = ft_trim_path(path);
	if (!trimmed_path)
	{
		texture->data = NULL;
		return (exit_error("Error/n Memory allocation"), 0);
	}
	img_ptr = mlx_xpm_file_to_image(game->mlx, trimmed_path, &texture->width,
			&texture->height);
	free(trimmed_path);
	if (!img_ptr)
	{
		texture->data = NULL;
		return (exit_error("Error/n Can not load texture "), 0);
	}
	if (original_path)
		free(original_path);
	texture->img = img_ptr;
	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (1);
}
