/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:26:23 by vtenigin          #+#    #+#             */
/*   Updated: 2017/03/13 22:11:49 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	checkreg(t_en *env, char *arg, int i, int op)
{
	int r;

	if (!(T_REG & g_ops[op].args[i]))
		showerr("wrong argument");
	if (!*arg)
		showerr("arg syntax error no arg");
	r = ft_atoi(arg);
	if (r > REG_NUMBER || r < 1)
		showerr("wrong registry number");
	while (*arg)
	{
		if (!ft_isnumber(arg))
			showerr("arg syntax error not a number reg");
		arg++;
	}
	env->header->prog_size++;
}

void	validlabel(t_label *label, char *str)
{
	while (label)
	{
		if (!ft_strcmp(label->label, str))
			return ;
		label = label->next;
	}
	showerr("nonexistent label argument");
}

void	checkind(t_en *env, char *arg, int i, int op)
{
	if (!(T_IND & g_ops[op].args[i]))
		showerr("wrong argument");
	if (ft_strlen(arg) < 1)
		showerr("arg syntax error too short ind");
	if (arg[0] == LABEL_CHAR)
	{
		if (!islabel(arg, 1, ft_strlen(arg)))
			showerr("invalid label");
		validlabel(env->label, arg + 1);
	}
	else
		while (*arg)
		{
			if (!ft_isnumber(arg))
				showerr("arg syntax error not a number ind");
			arg++;
		}
	env->header->prog_size += IND_SIZE;
}

void	checkdir(t_en *env, char *arg, int i, int op)
{
	if (!(T_DIR & g_ops[op].args[i]))
		showerr("wrong argument");
	if (ft_strlen(arg) < 1)
		showerr("arg syntax error too short dir");
	if (arg[0] == LABEL_CHAR)
	{
		if (!islabel(arg, 1, ft_strlen(arg)))
			showerr("invalid label");
		validlabel(env->label, arg + 1);
	}
	else
		while (*arg)
		{
			if (!ft_isnumber(arg))
				showerr("arg syntax error not a number dir");
			arg++;
		}
	env->header->prog_size += (g_ops[op].index) ? IND_SIZE : DIR_SIZE;
}

void	validargs(t_en *env, char **args, int op)
{
	int i;

	i = spllen(args);
	if (g_ops[op].nargs != i)
		showerr("wrong number of arguments");
	i = 0;
	while (args[i])
	{
		args[i] = trimfree(args[i]);
		if (args[i][0] == 'r')
			checkreg(env, args[i] + 1, i, op);
		else if (args[i][0] == DIRECT_CHAR)
			checkdir(env, args[i] + 1, i, op);
		else
			checkind(env, args[i], i, op);
		i++;
	}
	env->header->prog_size += (g_ops[op].acb) ? 2 : 1;
	addcode(env, op, args);
}
