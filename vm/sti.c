/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 21:55:11 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/29 23:38:22 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	get_args2(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b01011000)
	{
		proc->args[0] = e->memory[MODA(proc->pc + 2)];
		proc->args[1] = e->memory[MODA(proc->pc + 3)];
		proc->args[2] = get_hex_sum((e->memory[MODA(proc->pc + 4)]),
		(e->memory[MODA(proc->pc + 5)]));
		proc->to_inc = 6;
	}
	else if (proc->acb == 0b01101000 || proc->acb == 0b01111000)
	{
		proc->args[0] = e->memory[MODA(proc->pc + 2)];
		proc->args[1] = get_hex_sum((e->memory[MODA(proc->pc + 3)]),
		(e->memory[MODA(proc->pc + 4)]));
		proc->args[2] = get_hex_sum((e->memory[MODA(proc->pc + 5)]),
		(e->memory[MODA(proc->pc + 6)]));
		proc->to_inc = 7;
	}
}

static void	get_args(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b01010100)
	{
		proc->args[0] = e->memory[MODA(proc->pc + 2)];
		proc->args[1] = e->memory[MODA(proc->pc + 3)];
		proc->args[2] = e->memory[MODA(proc->pc + 4)];
		proc->to_inc = 5;
	}
	else if (proc->acb == 0b01100100)
	{
		proc->args[0] = e->memory[MODA(proc->pc + 2)];
		proc->args[1] = get_hex_sum(e->memory[MODA(proc->pc + 3)],
			e->memory[MODA(proc->pc + 4)]);
		proc->args[2] = e->memory[MODA(proc->pc + 5)];
		proc->to_inc = 6;
	}
	else if (proc->acb == 0b01110100)
	{
		proc->args[0] = e->memory[MODA(proc->pc + 2)];
		proc->args[1] = get_hex_sum((e->memory[MODA(proc->pc + 3)]),
		(e->memory[MODA(proc->pc + 4)]));
		proc->to_inc = 5;
	}
	get_args2(e, proc);
}

static int	is_reg(int a1, int a2)
{
	if (a1 > 0 && a1 < 17 && a2 > 0 && a2 < 17)
		return (1);
	return (0);
}

static int	get_sum(t_en *e, t_proc *proc)
{
	int	ret;

	ret = 0;
	if (proc->acb == 0b01010100 && is_reg(proc->args[1] - 1, proc->args[2] - 1))
		ret = proc->reg[proc->args[1] - 1] + proc->reg[proc->args[2] - 1];
	else if (proc->acb == 0b01100100)
		ret = proc->args[1] + proc->reg[proc->args[2] - 1];
	else if (proc->acb == 0b01110100)
		ret = proc->reg[proc->args[2] - 1]
		+ fill_reg(e->memory[MODA(proc->pc + proc->args[1])]);
	else if (proc->acb == 0b01011000)
		ret = proc->reg[proc->args[1] - 1] + proc->args[2];
	else if (proc->acb == 0b01101000)
		ret = proc->args[1] + proc->args[2];
	else if (proc->acb == 0b01111000)
		ret = fill_reg(e->memory[MODA(proc->pc
			+ proc->args[1])]) + proc->args[2];
	return (ret);
}

void		sti(t_en *e, t_proc *proc)
{
	unsigned int	adress;
	int				i;
	int				tab[4];

	i = -1;
	get_args(e, proc);
	adress = MODA(proc->pc + get_sum(e, proc));
	while (i++ < 4)
		tab[i] = MODA(adress + i);
	if (adress == 0)
		proc->carry = 0;
	else
	{
		e->memory[MODA(tab[3])] = proc->reg[proc->args[0] - 1];
		e->memory[MODA(tab[2])] = proc->reg[proc->args[0] - 1] >> 8;
		e->memory[MODA(tab[1])] = proc->reg[proc->args[0] - 1] >> 16;
		e->memory[MODA(adress)] = proc->reg[proc->args[0] - 1] >> 24;
		e->color[MODA(tab[3])] = proc->color;
		e->color[MODA(tab[2])] = proc->color;
		e->color[MODA(tab[1])] = proc->color;
		e->color[MODA(adress)] = proc->color;
	}
	proc->pc = MODA(proc->pc + proc->to_inc);
	proc->to_inc = 1;
	proc->op = 0;
}
