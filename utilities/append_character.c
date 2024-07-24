/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:09:38 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/23 13:19:23 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

#define START					0
#define NEW_AND_END_CHARACTERS	2

/**
 * 🔹 Name: append_character
 * ------------------------
 * 📝 Description: add a character to the end of an allocated string.
 *
 * 📌 Parameters:
 * → const char character : the character to add.
 * → t_string old_string : the string to add the character to.
 *
 * 🔄 Return value:
 * ↦ t_string : the extended string.
 *
 * ⚠️ Error management: none.
 */
t_string	append_character(const char character, t_string old_string)
{
	t_string	new_string;
	t_index		index;

	set_memory((void **)&new_string,
		get_length(old_string, NULL_CHARACTER) + NEW_AND_END_CHARACTERS);
	index = START;
	if (old_string)
		while (*old_string)
			new_string[index++] = *old_string++;
	new_string[index] = character;
	return (new_string);
}
