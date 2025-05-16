/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:31:03 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/15 17:24:29 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector2d.h"

t_vector2d	vector2d(float x, float y)
{
	return ((t_vector2d){x, y});
}

t_vector2d	vector2d_add(t_vector2d a, t_vector2d b)
{
	t_vector2d	v;

	v.x = a.x + b.x;
	v.y = a.y + b.y;
	return (v);
}

t_vector2d	vector2d_substract(t_vector2d a, t_vector2d b)
{
	t_vector2d	v;

	v.x = a.x - b.x;
	v.y = a.y - b.y;
	return (v);
}

t_vector2d	vector2d_multiply(t_vector2d a, t_vector2d b)
{
	t_vector2d	v;

	v.x = a.x * b.x;
	v.y = a.y * b.y;
	return (v);
}

t_vector2d	vector2d_divide(t_vector2d a, t_vector2d b)
{
	t_vector2d	v;

	v.x = a.x / b.x;
	v.y = a.y / b.y;
	return (v);
}
