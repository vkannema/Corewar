/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:33:31 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/15 18:44:51 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_and(t_en *e, t_proc *proc)
{
	int	res;

	get_args_axo(e, proc);
	res = proc->args[0] & proc->args[1];
	if (res == 0)
	{
		proc->carry = 1;
		proc->pc = MODA(proc->pc + proc->to_inc);
	}
	else
	{
		proc->carry = 0;
		proc->reg[proc->args[2] - 1] = res;
		proc->pc = MODA(proc->pc + proc->to_inc);
	}
	proc->to_inc = 1;
	proc->op = 0;
}
