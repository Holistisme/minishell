/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:33:55 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/24 13:39:14 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

#define OPENED_PIPE	-1

/**
 * 🔹 Name: cut_tokens
 * ------------------------
 * 📝 Description: binds each token to the command, until the pipe or the end.
 *
 * 📌 Parameters:
 * → t_command_setup *setup : the command initialization manager.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: none.
 */
void	cut_tokens(t_command_setup *setup)
{
	setup->current_token = setup->first_token;
	while (setup->current_token && setup->current_token->type != PIPELINE)
		setup->current_token = setup->current_token->next;
	if (setup->current_token)
	{
		setup->current_command->outfile = OPENED_PIPE;
		setup->current_token->previous->next = NULL;
		setup->current_token->next->previous = NULL;
		setup->current_token = setup->current_token->next;
	}
	setup->first_token = setup->current_token;
}

/**
 * 🔹 Name: add_command
 * ------------------------
 * 📝 Description: allocates memory, initializes each command, and adds tokens.
 *
 * 📌 Parameters:
 * → t_command_setup *setup : the command initialization manager.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: none.
 */
void	add_command(t_command_setup *setup)
{
	set_memory((void **)&setup->current_command, sizeof(t_command));
	setup->current_command->outfile = STDOUT_FILENO;
	setup->current_command->error = NULL;
	setup->current_command->token = setup->first_token;
	cut_tokens(setup);
}

/**
 * 🔹 Name: handle_tokens
 * ------------------------
 * 📝 Description: isolates and connects each command together.
 *
 * 📌 Parameters:
 * → t_command_setup *setup : the command initialization manager.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: none.
 */
static void	handle_tokens(t_command_setup *setup)
{
	while (setup->first_token)
	{
		add_command(setup);
		if (!setup->first_command)
		{
			setup->first_command = setup->current_command;
			setup->last_command = setup->current_command;
		}
		else
		{
			setup->last_command->next = setup->current_command;
			setup->last_command = setup->current_command;
		}
	}
}

/**
 * 🔹 Name: set_commands
 * ------------------------
 * 📝 Description: retrieves input, saves and splits into commands.
 *
 * 📌 Parameters:
 * → const t_string inputs : user inputs.
 *
 * 🔄 Return value:
 * ↦ t_command *first : the first command of the order.
 *
 * ⚠️ Error management: none.
 */
t_command	*set_commands(const t_string inputs)
{
	t_command_setup	*setup;

	if (!inputs)
		return (NULL);
	add_history(inputs);
	set_memory((void **)&setup, sizeof(t_command_setup));
	setup->first_token = set_tokens(inputs);
	setup->first_command = NULL;
	handle_tokens(setup);
	free(inputs);
	if (setup->last_command)
		setup->last_command->next = NULL;
	return (setup->first_command);
}
