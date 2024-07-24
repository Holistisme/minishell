/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:37:25 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/23 12:52:41 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

#define ONE_CHARACTER		1
#define ERROR_WARNING_SIZE	16

/**
 * 🔹 Name: write_error
 * ------------------------
 * 📝 Description: writes the nature of an error to the associated output.
 * 
 * 📌 Parameters:
 * → const t_string string : the error message to write.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: none.
 */
static void	write_error(const t_string string)
{
	write(STDERR_FILENO, "⚠️  ERROR:\n", ERROR_WARNING_SIZE);
	if (string)
		write(STDERR_FILENO, string, get_length(string, NULL_CHARACTER));
	write(STDERR_FILENO, "\n", ONE_CHARACTER);
}

/**
 * 🔹 Name: terminate_program
 * ------------------------
 * 📝 Description: informs user of the error, frees memory and kills program.
 * 
 * 📌 Parameters:
 * → const t_error error : the error code terminating the program.
 *
 * 🔄 Return value:
 * ↦ death : ends the program with or against one's will.
 *
 * ⚠️ Error management: THIS is THE error handler.
 */
void	terminate_program(const t_error error)
{
	if (error == ERR_ALLOC)
		write_error("Failed memory allocation!");
	else
		write_error(NULL);
	manage_memory(FREE, NULL);
	exit(error);
}
