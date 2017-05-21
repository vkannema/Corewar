/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 15:14:21 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/16 15:01:37 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	get_args_zjmp(t_en *e, t_proc *proc)
{
	proc->args[0] = get_hex_sum(MODA(e->memory[proc->pc + 1]),
	MODA(e->memory[proc->pc + 2]));
}

void		zjmp(t_en *e, t_proc *proc)
{
	int	res;

	if (proc->carry == 0)
		proc->pc = MODA(proc->pc + 3);
	else
	{
		get_args_zjmp(e, proc);
		res = MODA(proc->pc + proc->args[0]);
		proc->pc = MODA(res);
	}
	proc->to_inc = 1;
	proc->op = 0;
}
