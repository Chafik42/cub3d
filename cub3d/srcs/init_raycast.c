/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <qatar75020@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:26:45 by cmarouf           #+#    #+#             */
/*   Updated: 2022/04/17 01:50:40 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_texture_rgb(t_ray *ray, t_parse *parse)
{
	ray->txt[0].path = NULL;
	ray->txt[1].path = parse->npath;
	ray->txt[2].path = parse->spath;
	ray->txt[3].path = parse->epath;
	ray->txt[4].path = parse->wpath;
	ray->colorc = parse->colorc;
	ray->colorf = parse->colorf;
}

void	init_mlx_var(t_ray *ray, t_parse *parse)
{
	ray->quit = 0;
	ray->move = 0;
	ray->firsta = 1;
	ray->map = parse->map + 6;
}

void	init_position_var(t_ray *ray)
{
	ray->pdx = cos(ray->pa) * 5;
	ray->pdy = sin(ray->pa) * 5;
	ray->width = count_x(ray->map) * BLOCSIZE;
	ray->height = count_y(ray->map) * BLOCSIZE;
	ray->x = count_x(ray->map);
	ray->y = count_y(ray->map);
}

void	init_raycasting(t_parse *parse)
{
	t_ray	ray;

	init_mlx_var(&ray, parse);
	get_texture_rgb(&ray, parse);
	spawn_point(&ray);
	angle_point(&ray);
	init_position_var(&ray);
	ray.quit = create_mlx(&ray);
	if (ray.quit == 1)
	{
		free_data(parse);
		free_mlx(&ray);
		return ;
	}
	raycasting(&ray);
	mlx_loop_hook(ray.mlx, &rayloop, &ray);
	mlx_hook(ray.win, 17, (1L << 17), &quit, &ray);
	mlx_hook(ray.win, KeyPress, KeyRelease, &key_handle, &ray);
	mlx_loop(ray.mlx);
	free_data(parse);
	free_mlx(&ray);
}