/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alphanumeric.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:54:11 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/24 13:10:24 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

#define UNDERSCORE	'_'

/**
 * 🔹 Name: is_alphanumeric
 * ------------------------
 * 📝 Description: checks if a character is alphanumeric.
 *
 * 📌 Parameters:
 * → const char character : the character to check.
 *
 * 🔄 Return value:
 * ↦ TRUE : whether the character is a letter, number, or underscore.
 * ↦ FALSE : if the character is something else.
 *
 * ⚠️ Error management: returns FALSE if the string is invalid.
 */
t_bool	is_alphanumeric(const char character)
{
	if ((character >= 'A' && character <= 'Z')
		|| (character >= 'a' && character <= 'z')
		|| character == UNDERSCORE)
		return (TRUE);
	return (FALSE);
}
