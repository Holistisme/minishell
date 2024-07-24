/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:21:29 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/24 13:11:09 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/**
 * 🔹 Name: get_length
 * ------------------------
 * 📝 Description: calculates the size of a string up to the delimiters
 *
 * 📌 Parameters:
 * → const t_string string : the string to scan.
 * → const t_string delimiters : the different delimiters of the string.
 *
 * 🔄 Return value:
 * ↦ size_t : Returns the size of the string up to the delimitation.
 * ↦ If no delimiters, returns the size of the total string.
 * 
 * ⚠️ Error management: returns 0 if the string is invalid.
 */
size_t	get_length(const t_string string, const t_string delimiters)
{
	size_t	size;

	size = 0;
	if (string)
		while (string[size] && !is_inside(string[size], delimiters))
			++size;
	return (size);
}
