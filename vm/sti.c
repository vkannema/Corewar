/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 21:55:11 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/17 15:41:20 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	is_valid(t_en *e, t_proc *proc, int jump)
{
	char	read;

	read = (char)((e->memory[MODA(proc->pc + jump)]));
	if (read > 0 && read <= REG_NUMBER)
		return (1);
	return (0);
}

static int	read_hexa(t_en *e, t_proc *proc, char type, int jump)
{
	char	read1;
	short	read2;
	int		read4;

	if (type == REG_CODE)
	{
		read1 = (e->memory[MODA(proc->pc + jump)]);
		return (proc->reg[read1 - 1]);
	}
	read2 = (short)((e->memory[MODA(proc->pc + jump)]) << 8 |
			(e->memory[MODA(proc->pc + jump + 1)]));
	if (type == DIR_CODE)
		return ((int)read2);
	read2 = MODR(read2);
	read4 = (int)((e->memory[MODA(proc->pc + read2)]) << 24 |
			(e->memory[MODA(proc->pc + read2 + 1)]) << 16 |
			(e->memory[MODA(proc->pc + read2 + 2)]) << 8 |
			(e->memory[MODA(proc->pc + read2 + 3)]));
	return (read4);
}

static int	get_terms(t_en *e, t_proc *proc, t_sti *s, char type)
{
	int		ret;

	ret = 1;
	if (type == REG_CODE && !is_valid(e, proc, s->jump))
		ret = 0;
	else
		s->where += read_hexa(e, proc, type, s->jump);
	s->jump = type == REG_CODE ? s->jump + 1 : s->jump + 2;
	return (ret);
}

static int	get_instruction(t_en *e, t_proc *proc, t_sti *s)
{
	char	reg;
	int		ret;
	char	type;

	ret = 1;
	reg = (char)((e->memory[MODA(proc->pc + 2)]));
	if (!(reg > 0 && reg <= REG_NUMBER))
		return (0);
	s->value = proc->reg[reg - 1];
	s->jump = 3;
	s->where = 0;
	s->acb = (e->memory[MODA(proc->pc + 1)]);
	type = (s->acb >> 4) & 3;
	if (!get_terms(e, proc, s, type))
		ret = 0;
	type = (s->acb >> 2) & 3;
	if (!get_terms(e, proc, s, type))
		ret = 0;
	s->where = MODR(s->where);
	return (ret);
}

void		sti(t_en *e, t_proc *proc)
{
	t_sti	s;
	int		i;

	if (get_instruction(e, proc, &s))
	{
		proc->carry = 0;
		i = -1;
		while (++i < 4)
		{
			e->memory[MODA((proc->pc + s.where + i))] =
				(s.value >> (8 * (3 - i))) & 0xff;
		}
	}
	else
	{
		s.jump = definejump(proc->acb);
		proc->carry = 1;
	}
	proc->pc += s.jump;
	proc->to_inc = 1;
	proc->op = 0;
}
