/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:30:15 by nbenhami          #+#    #+#             */
/*   Updated: 2025/05/17 15:34:17 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR2D_H
# define VECTOR2D_H

# include <math.h>

typedef struct s_vector2d
{
	float	x;
	float	y;
}	t_vector2d;

t_vector2d	vector2d(float x, float y);

t_vector2d	vector2d_add(t_vector2d a, t_vector2d b);
t_vector2d	vector2d_substract(t_vector2d a, t_vector2d b);
t_vector2d	vector2d_multiply(t_vector2d a, t_vector2d b);
t_vector2d	vector2d_scale(t_vector2d a, float scale);
t_vector2d	vector2d_divide(t_vector2d a, float div);
t_vector2d	vector2d_rotate(t_vector2d dir, float angle);

#endif /* VECTOR2D_H */