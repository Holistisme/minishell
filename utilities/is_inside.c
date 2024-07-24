/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_inside.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:35:14 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/24 13:08:29 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/**
 * 🔹 Name: is_inside
 * ------------------------
 * 📝 Description: checks if a character is within a string.
 *
 * 📌 Parameters:
 * → const char character : the character to search for.
 * → t_string string : the string to scan.
 *
 * 🔄 Return value:
 * ↦ TRUE : if the character was found.
 * ↦ FALSE : if the character was not found.
 *
 * ⚠️ Error management: none.
 */
t_bool	is_inside(const char character, t_string string)
{
	if (string)
		while (*string)
			if (*string++ == character)
				return (TRUE);
	return (FALSE);
}
