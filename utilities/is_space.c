/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:09:53 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/24 13:08:05 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

#define VERTICAL_TAB	'\v'
#define CARRIAGE_RETURN	'\r'

/**
 * 🔹 Name: is_space
 * ------------------------
 * 📝 Description: compares the transferred character to "C" spaces
 *
 * 📌 Parameters:
 * → const char character : the character to compare.
 *
 * 🔄 Return value:
 * ↦ TRUE : if the comparison is.
 * ↦ FALSE : if the comparison is not.
 *
 * ⚠️ Error management: none.
 */
t_bool	is_space(const char character)
{
	if (is_inside(character, POSIX_SPACE))
		return (TRUE);
	return (FALSE);
}
