/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:11:43 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/18 23:37:02 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	pxl_to_img(t_cub *cub, float x, float y, int i)
{
	char	*tmp;
	t_text	*ptr;

	ptr = cub->text;
	tmp = ptr[i].addr + (int)(y * ptr[i].size + x * (ptr[i].bpp / 8));
	*(unsigned int *)tmp = cub->color;
}

void	pxl_to_ray(t_cub *cub, float x, float y, unsigned int color)
{
	char	*tmp;
	//t_text	*ptr;
	int		size;
	int		completer;

	//ptr = cub->text;
	//if (!ptr[0].addr)
	if (!cub->rayaddr)
		return ;
	if (y == 0 && x < 0)
		x = 0;
	if (y < 0 && x)
		y = 0;
	//size = (int)(y * ptr[0].size + x * (ptr[0].bpp / 8));
	size = (int)(y * cub->r_size + x * (cub->r_bpp / 8));
	if (size < 0 || size >= RES)
		return ;
	completer = 0;
	//tmp = ptr[0].addr + size;
	tmp = cub->rayaddr + size;
	while (completer < 4)
	{
		*((unsigned int *)tmp + completer) = color;
		completer++;
	}
}

unsigned int	pxl_from_img(t_cub *cub, int x, int y, int i)
{
	char	*tmp;
	t_text	*ptr;
	int		size;

	ptr = cub->text;
	if (y == 0 && x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	size = (int)(y * ptr[i].size + x * (ptr[i].bpp / 8));
	if (size < 0 || size >= 1228800) //ptr[i].res
		return (0xffffff);
	tmp = ptr[i].addr + size;
	if (cub->ray->r == 0)
		printf("pxl = %u >> size = %d >>> x = %d >>> y = %d\n", (*(unsigned int *)tmp), size, x , y);
	return (*(unsigned int *)tmp);
}

unsigned int	rgb_to_hex(unsigned int r, unsigned int g, unsigned int b)
{
	return ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}

unsigned int	shade(unsigned int color, float shader)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (shader < 0)
		shader = 0;
	if (shader > 1)
		shader = 1;
	r = (color >> 16) * shader;
	g = ((color >> 8) * 0x00ff) * shader;
	b = (color & 0x0000ff) * shader;
	return ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}
