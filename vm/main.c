/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 21:47:53 by vtenigin          #+#    #+#             */
/*   Updated: 2017/07/03 10:06:34 by vkannemacher     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	winner(t_en *e)
{
	t_champ *champ;

	champ = e->champ;
	while (champ)
	{
		if (champ->id == e->last_rapported)
			ft_printf("Contestant %d, \"%s\", has won !\n",
			-(champ->id), champ->name);
		champ = champ->next;
	}
}

void		showusage()
{
	ft_printf("Usage:\n\
 	Example: ./corewar -i -n -1 filename.cor\n\
 	GUI: ./corewar -i [Players]\n\
 	Default Player Numbers: 1, 2, 3, 4\n\
 	Change Player Number: -n -1 filename.cor\n\
 	Dump: ./corewar -dump 300 [Players](prints the memory after 300 cycles)\n");
	exit(EXIT_FAILURE);
}

int		main(int ac, char **av)
{
	t_en	env;
	int		i;

	envinit(&env);
	if (ac < 2)
		showusage();
	i = 0;
	if (get_bonus(av[i + 1], &env))
		i++;
	if (get_dump(av[i + 1], av[i + 2], &env))
		i += 2;
	while (av[++i])
	{
		if (is_assignment(av[i], av[i + 1], &env))
			i += 2;
		readchamp(&env, av[i]);
	}
	writechamp(&env);
	makeproc(&env);
	ft_print_dump_init(&env);
	env.proc->start = 1;
	move_proc(&env);
	winner(&env);
	return (0);
}
