/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:12:06 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/23 12:30:59 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

#define AT_SIGN	'@'
#define COLON	':'
#define TILDE	'~'

/**
 * 🔹 Name: cut_pwd
 * ------------------------
 * 📝 Description: cut the working directory value for the prompt.
 * 
 * 📌 Parameters:
 * → void : the function takes no parameters.
 *
 * 🔄 Return value:
 * ↦ t_string cut : the character string of the working directory value cut.
 *
 * ⚠️ Error management: none.
 */
static t_string	cut_pwd(void)
{
	const t_string	pwd = getenv("PWD");
	t_string		cut;

	cut = append_character(TILDE, NULL);
	if (pwd)
		cut = append_string(cut,
				pwd + get_length(getenv("HOME"), NULL_CHARACTER));
	return (cut);
}

/**
 * 🔹 Name: get_prompt
 * ------------------------
 * 📝 Description: assembles the prompt with the different environment variables.
 * 
 * 📌 Parameters:
 * → void : the function takes no parameters.
 *
 * 🔄 Return value:
 * ↦ t_string prompt : the character string to display the prompt.
 *
 * ⚠️ Error management: none.
 */
t_string	get_prompt(void)
{
	t_string	prompt;

	prompt = append_string(NULL, getenv("LOGNAME"));
	prompt = append_character(COLON, prompt);
	prompt = append_string(prompt, getenv("NAME"));
	prompt = append_character(AT_SIGN, prompt);
	prompt = append_string(prompt, cut_pwd());
	prompt = append_string(prompt, "$ ");
	return (prompt);
}
