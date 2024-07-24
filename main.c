/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:03:14 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/24 13:41:52 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

#define FOREVER	1

/**
 * 🔹 Name: main
 * ------------------------
 * 📝 Description: main function of the program, retrieves the command.
 *
 * 📌 Parameters:
 * → void : no parameter is taken into account.
 *
 * 🔄 Return value:
 * ↦ EXIT_SUCCESS : the success of the program.
 *
 * ⚠️ Error management: none.
 */
int	main(void)
{
	t_command	*first_command;

	while (FOREVER)
	{
		first_command = set_commands(readline(get_prompt()));
		manage_memory(FREE, NULL);
	}
	return (EXIT_SUCCESS);
}
