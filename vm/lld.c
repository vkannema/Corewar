/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 22:17:23 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/30 15:31:40 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	get_args_ld(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b11010000)
	{
		proc->args[0] = get_hex_sum(e->memory[MODA(proc->pc + 2)],
		e->memory[MODA(proc->pc + 3)]);
		proc->args[1] = e->memory[MODA(proc->pc + 4)];
		proc->to_inc = 5;
	}
	else if (proc->acb == 0b10010000)
	{
		proc->args[0] = get_hex_sum1(e->memory[MODA(proc->pc + 2)],
			e->memory[MODA(proc->pc + 3)], e->memory[MODA(proc->pc + 4)],
			e->memory[MODA(proc->pc + 5)]);
		proc->args[1] = e->memory[MODA(proc->pc + 6)];
		proc->to_inc = 7;
	}
}

void		lld(t_en *e, t_proc *proc)
{
	int	res;

	get_args_ld(e, proc);
	if (is_reg(proc->args[1] - 1, 0, 0))
	{
		if (proc->acb == 0b11010000 && proc->args[0])
		{
			res = proc->pc + MODR(proc->args[0]);
			proc->reg[proc->args[1] - 1] = fill_reg(
				get_hex_sum(e->memory[MODA(res)], e->memory[MODA(res) + 1]));
			proc->carry = 0;
		}
		else if (proc->acb == 0b10010000 && proc->args[0])
			proc->reg[proc->args[1] - 1] = (int)proc->args[0];
		else if (proc->args[0] == 0)
			proc->carry = 1;
	}
	else
		proc->carry = 1;
	proc->pc = MODA(proc->pc + proc->to_inc);
	proc->to_inc = 1;
	proc->op = 0;
}
