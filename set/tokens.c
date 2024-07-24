/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:53:48 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/24 13:26:04 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

#define NONE			0
#define VARIABLE		'$'
#define SINGLE_QUOTE	'\''
#define QUOTES			"\'\""

/**
 * 🔹 Name: fetch_variable_name
 * ------------------------
 * 📝 Description: isolates the name of an environment variable.
 *
 * 📌 Parameters:
 * → const t_string inputs : user inputs.
 *
 * 🔄 Return value:
 * ↦ t_string name : the name of the environment variable.
 *
 * ⚠️ Error management: none.
 */
static t_string	fetch_variable_name(t_string *inputs)
{
	t_string	name;

	name = NULL;
	while (is_alphanumeric(**inputs))
		name = append_character(*(*inputs)++, name);
	return (name);
}

/**
 * 🔹 Name: save_characters
 * ------------------------
 * 📝 Description: saves a token character by character, while checking quotes.
 *
 * 📌 Parameters:
 * → t_token_setup *setup : the token initialization manager.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: none.
 */
static void	save_characters(t_token_setup *setup)
{
	if (*setup->inputs == VARIABLE && setup->active_quote != SINGLE_QUOTE)
	{
		++setup->inputs;
		setup->current_token->value
			= append_string(setup->current_token->value,
				getenv(fetch_variable_name(&setup->inputs)));
	}
	else
		setup->current_token->value
			= append_character(*setup->inputs++, setup->current_token->value);
}

/**
 * 🔹 Name: fetch_token
 * ------------------------
 * 📝 Description: allocate memory for token, checks if it's a pipe, saves it.
 *
 * 📌 Parameters:
 * → t_token_setup *setup : the token initialization manager.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: none.
 */
static void	fetch_token(t_token_setup *setup)
{
	set_memory((void **)&setup->current_token, sizeof(t_token));
	setup->current_token->value = NULL;
	if (*setup->inputs == PIPE)
	{
		setup->current_token->type = PIPELINE;
		save_characters(setup);
	}
	else
	{
		while (*setup->inputs && !is_space(*setup->inputs)
			&& *setup->inputs != PIPE)
		{
			setup->active_quote = NONE;
			if (is_inside(*setup->inputs, QUOTES))
			{
				setup->active_quote = *setup->inputs++;
				while (*setup->inputs && *setup->inputs != setup->active_quote)
					save_characters(setup);
				setup->inputs++;
			}
			else
				save_characters(setup);
		}
	}
}

/**
 * 🔹 Name: add_token
 * ------------------------
 * 📝 Description: isolates then connects each token to their list.
 *
 * 📌 Parameters:
 * → t_token_setup *setup : the token initialization manager.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: none.
 */
static void	add_token(t_token_setup *setup)
{
	fetch_token(setup);
	if (!setup->first_token)
	{
		setup->first_token = setup->current_token;
		setup->last_token = setup->current_token;
		setup->first_token->previous = NULL;
	}
	else
	{
		setup->current_token->previous = setup->last_token;
		setup->last_token->next = setup->current_token;
		setup->last_token = setup->current_token;
	}
}

/**
 * 🔹 Name: set_tokens
 * ------------------------
 * 📝 Description: created an init handler and adds each spaced token.
 *
 * 📌 Parameters:
 * → const t_string inputs : user inputs.
 *
 * 🔄 Return value:
 * ↦ t_token *first : the first token of the order.
 *
 * ⚠️ Error management: none.
 */
t_token	*set_tokens(const t_string inputs)
{
	t_token_setup	*setup;

	set_memory((void **)&setup, sizeof(t_token_setup));
	setup->first_token = NULL;
	setup->inputs = inputs;
	while (*setup->inputs)
	{
		if (!is_inside(*setup->inputs, POSIX_SPACE))
			add_token(setup);
		else
			++setup->inputs;
	}
	setup->current_token->next = NULL;
	return (setup->first_token);
}
