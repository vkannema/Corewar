/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:33:05 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/20 15:37:16 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	get_args(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b01010100)
	{
		proc->args[0] = e->memory[MODA(proc->pc + 2)];
		proc->args[1] = e->memory[MODA(proc->pc + 3)];
		proc->args[2] = e->memory[MODA(proc->pc + 4)];
		proc->to_inc = 5;
	}
}

void		add(t_en *e, t_proc *proc)
{
	int	res;

	get_args(e, proc);
	system("clear");
	printmemory(e);
	sleep(3);
	ft_printf("proc->pc %d\n", proc->pc);
	res = proc->reg[proc->args[0] - 1] + proc->reg[proc->args[1] - 1];
	if (res == 0)
	{
		proc->reg[proc->args[2] - 1] = res;
		proc->carry = 1;
		proc->to_inc = 5;
	}
	else
	{
		proc->carry = 0;
		proc->reg[proc->args[2] - 1] = res;
	}
	proc->pc = MODA(proc->pc + proc->to_inc);
	proc->to_inc = 1;
	proc->op = 0;
}
