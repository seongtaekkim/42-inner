/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongtki <seongtki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:27:01 by seongtki          #+#    #+#             */
/*   Updated: 2022/09/07 17:42:55 by seongtki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

int	abs_one(int n)
{
	if (n <= 0)
		return (-1);
	else
		return (1);
}

double	degree_to_radian(int degree)
{
	return (degree * 3.14159265F / 180.0F);
}
