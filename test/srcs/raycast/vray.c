/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vray.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:50:23 by anremiki          #+#    #+#             */
/*   Updated: 2022/05/18 01:35:14 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	vert_door_txt(t_cub *cub, t_ray *ray, int dir)
{
	ray->right = ((int)ray->ry - (int)cub->door) % 128;
	ray->left = 128 - ((int)ray->ry + (int)cub->door) % 128;
	if (dir == 1)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->right, 8))); //s
	if (dir == 2)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->left, 8))); //s
	if (dir == 3)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->right, 8))); //ms
	if (dir == 4)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->left, 8))); //ms
	return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->left, 8))); //s
}

unsigned int	vertical_texture(t_cub *cub, t_ray *ray, int dir)
{
	float	s;
	float	ms;

	s = ray->shadow;
	//ms = s - 0.3;
	ms = s;
	if (cub->glass)
		return (vert_door_txt(cub, ray, dir));
	if (dir == 1) //ray->ray == 1 && dir == 1
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->right, 1))); //s
	if (dir == 2)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->left, 2))); //s
	if (dir == 3)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->right, 5))); //ms
	if (dir == 4)
		return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->left, 5))); //ms
	(void)s;
	(void)ms;
	return ((pxl_from_img(cub, (int)ray->curr_px % 64, ray->left, 5))); //ms
}

void	dda_vertical(t_cub *cub, t_ray *ray)
{
	cub->vglass = 0;
	while (ray->limit < cub->ex)
	{
		ray->mx = (int)ray->rx;
		ray->my = (int)ray->ry;
		if ((ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1 &&
					ray->my > -1) && check_valid(cub->exp[ray->my][ray->mx],
						"3"))
		{
			if (ray->vdir == 1)
			{
				if (ray->my % 64 < 32)
				{
					ray->rx = ray->rx + ray->yo / 64 * (32 - ray->my % 64);
					//ray->ry = ray->ry + (32 - ray->my % 64);
				}
				else
				{
					ray->rx = ray->rx + ray->yo / 64 * (ray->my % 64 - 32);
					//ray->ry = ray->ry + (ray->my % 64 - 32);
				}
			}
			else
			{
				if (64 - ray->my % 64 < 32)
				{
					ray->rx = ray->rx + ray->yo / 64 * (32 - (64 - ray->my % 64));
					//ray->ry = ray->ry + (32 - (64 - ray->my % 64));
				}
				else
				{
					ray->rx = ray->rx + ray->yo / 64 * (64 - ray->my % 64 - 32);
					//ray->ry = ray->ry + (64 - ray->my % 64 - 32);
				}
			}
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->vray = dist(cub->x , cub->y, ray->vx, ray->vy);
			break ;
		}
		if ((ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1 &&
					ray->my > -1) && check_valid(cub->exp[ray->my][ray->mx],
						" "))
		{
			ray->rx += ray->xo / 2;
			ray->ry += ray->yo / 2;
			if (((int)ray->ry % 64 - (int)cub->door) > 0 && ray->vdir == 1)
			{
				cub->vglass = 1;
				ray->vx = ray->rx;
				ray->vy = ray->ry;
				ray->vray = dist(cub->x , cub->y, ray->vx, ray->vy);
				break ;
			}
			if (64 - ((int)ray->ry % 64 + (int)cub->door) > 0 && ray->vdir == 2)
			{
				cub->vglass = 1;
				ray->vx = ray->rx;
				ray->vy = ray->ry;
				ray->vray = dist(cub->x , cub->y, ray->vx, ray->vy);
				break ;
			}
			ray->rx += ray->xo / 2;
			ray->ry += ray->yo / 2;
		}
		if ((ray->mx < cub->ex && ray->my < cub->ey && ray->mx > -1 &&
					ray->my > -1) && check_valid(cub->exp[ray->my][ray->mx],
						"12"))
		{
			if (cub->exp[ray->my][ray->mx] == '2')
				ray->vdir += 2;
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->vray = dist(cub->x , cub->y, ray->vx, ray->vy);
			break ;
		}
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		ray->limit++;
	}
}

void	vray(t_cub *cub, t_ray *ray)
{
	if (ray->ra == PI || ray->ra == 0)
	{
		ray->vdir = 0;
		ray->rx = cub->x;
		ray->ry = cub->y;
		ray->limit = 20;
	}
	else if (ray->ra > PI2 && ray->ra < PI3)
	{
		ray->vdir = 1;
		ray->rx = ray->npx - 0.0001;
		ray->ry = (cub->x - ray->rx) * ray->ntan + cub->y;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->ntan;
	}
	else if (ray->ra < PI2 || ray->ra > PI3)
	{
		ray->vdir = 2;
		ray->rx = ray->npx + 64;
		ray->ry = (cub->x - ray->rx) * ray->ntan + cub->y;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->ntan;
	}
	if (cub->debug && ray->r == NRAY / 2)
	{
		printf("VDIR = %d\n", ray->vdir);
		printf("npx = %.10lf\n", ray->npx);
		printf("vrx = %.10lf\n", ray->rx);
		printf("vry = %lf\n", ray->ry);
	}
	dda_vertical(cub, ray);
}
