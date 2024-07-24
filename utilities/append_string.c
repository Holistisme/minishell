/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:35:12 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/23 13:04:37 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/**
 * 🔹 Name: append_string
 * ------------------------
 * 📝 Description: adds one string to the end of another.
 *
 * 📌 Parameters:
 * → t_string destination : the character string to complete.
 * → t_string source : the character string to place at the end.
 *
 * 🔄 Return value:
 * ↦ t_string : the extended string.
 *
 * ⚠️ Error management: none.
 */
t_string	append_string(t_string destination, t_string source)
{
	if (source)
		while (*source)
			destination = append_character(*source++, destination);
	return (destination);
}
