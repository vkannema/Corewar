/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 11:35:05 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/24 17:34:49 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	arg2(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b01010100)
	{
		proc->args[0] = e->memory[MODA(proc->pc + 2)];
		proc->args[1] = e->memory[MODA(proc->pc + 3)];
		proc->args[2] = e->memory[MODA(proc->pc + 4)];
		proc->to_inc = 5;
	}
	else if (proc->acb == 0b10010100 || proc->acb == 0b11010100)
	{
		proc->args[0] = get_hex_sum(e->memory[MODA(proc->pc + 2)],
		e->memory[MODA(proc->pc + 3)]);
		proc->args[1] = e->memory[MODA(proc->pc + 4)];
		proc->args[2] = e->memory[MODA(proc->pc + 5)];
		proc->to_inc = 6;
	}
}

static void	get_args(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b01100100)
	{
		proc->args[0] = e->memory[MODA(proc->pc + 2)];
		proc->args[1] = get_hex_sum(e->memory[MODA(proc->pc + 3)],
		e->memory[MODA(proc->pc + 4)]);
		proc->args[2] = e->memory[MODA(proc->pc + 5)];
		proc->to_inc = 6;
	}
	else if (proc->acb == 0b10100100 || proc->acb == 0b11100100)
	{
		proc->args[0] = get_hex_sum(e->memory[MODA(proc->pc + 2)],
		e->memory[MODA(proc->pc + 3)]);
		proc->args[1] = get_hex_sum(e->memory[MODA(proc->pc + 4)],
		e->memory[MODA(proc->pc + 5)]);
		proc->args[2] = e->memory[MODA(proc->pc + 6)];
		proc->to_inc = 7;
	}
	else
		arg2(e, proc);
}

static int	get_sum(t_en *e, t_proc *proc)
{
	int ret;

	ret = 0;
	if (proc->acb == 0b01100100)
		ret = proc->reg[proc->args[0] - 1] + proc->args[1];
	else if (proc->acb == 0b10100100)
		ret = fill_reg(proc->args[0] + proc->args[1]);
	else if (proc->acb == 0b11100100)
		ret = fill_reg(e->memory[MODA(proc->pc + proc->args[0])] +
		proc->args[1]);
	else if (proc->acb == 0b01010100)
		ret = (int)(proc->reg[proc->args[1] - 1] +
			proc->reg[proc->args[0] - 1]);
	else if (proc->acb == 0b10010100)
		ret = proc->args[0] + proc->reg[proc->args[1]];
	else if (proc->acb == 0b11010100)
		ret = proc->reg[proc->args[0] - 1] + proc->reg[proc->args[1] - 1];
	return (ret);
}

static int	get_ldi(int pc, int res)
{
	int	ret;

	ret = 0;
	if (res > 32767)
	{
		ret = -(MODR(res));
		return (pc + ret);
	}
	return (pc + MODR(res));
}

void		ft_ldi(t_en *e, t_proc *proc)
{
	int	adress;

	get_args(e, proc);
	adress = get_sum(e, proc);
	adress = get_ldi(proc->pc, adress);
	if (adress == 0)
		proc->carry = 1;
	else
	{
		proc->reg[proc->args[2] - 1] = get_hex_sum1(e->memory[adress],
			e->memory[MODA(adress + 1)], e->memory[MODA(adress + 2)],
			e->memory[MODA(adress + 3)]);
		proc->carry = 0;
	}
	proc->pc = MODA(proc->pc + proc->to_inc);
	proc->to_inc = 1;
	proc->op = 0;
}
