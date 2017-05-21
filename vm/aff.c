/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 20:54:42 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/14 21:19:40 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_args(t_proc *proc)
{
	if (proc->acb == 0b01000000)
		proc->args[0] = MODA(proc->pc + 2);
	proc->to_inc = 3;
}

void	aff(t_en *e, t_proc *proc)
{
	int	ret;

	get_args(proc);
	ret = proc->reg[proc->args[0] - 1] % 256;
	if (ret == 0)
		proc->carry = 1;
	else
	{
		if (!e->bonus)
			ft_printf("%c\n", ret);
		else
			printw("LOLOLOLOL %c\n", ret);
		proc->carry = 0;
	}
	proc->op = 0;
	proc->pc = MODA(proc->pc + proc->to_inc);
	proc->to_inc = 0;
}
