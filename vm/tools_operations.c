/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 21:30:01 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/17 15:41:23 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			get_address(int pc, int arg)
{
	if (arg > 32767)
	{
		arg = -(arg);
		arg = MODA(arg);
		return (pc - arg);
	}
	arg = MODR(arg);
	return (pc + arg);
}

int			definejump(int acb)
{
	if (acb == 0b01010100)
		return (5);
	else if (acb == 0b01100100 || acb == 0b01110100 || acb == 0b01011000)
		return (6);
	else if (acb == 0b01101000 || acb == 0b01111000)
		return (7);
	return (1);
}
