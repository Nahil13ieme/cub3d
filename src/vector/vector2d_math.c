/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:08:55 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/16 21:25:05 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector2d.h"

t_vector2d	vector2d_scale(t_vector2d a, float scale)
{
	t_vector2d	v;

	v.x = a.x * scale;
	v.y = a.y * scale;
	return (v);
}

float	vector2d_length(t_vector2d v)
{
	float	length;

	length = (float)(sqrt((v.x * v.x) + (v.y * v.y)));
	return (length);
}

t_vector2d	vector2d_normalize(t_vector2d a)
{
	t_vector2d	v;
	float		length;

	length = vector2d_length(a);
	if (length == 0.f)
		return ((t_vector2d){0, 0});
	v.x = a.x / length;
	v.y = a.y / length;
	return (v);
}
