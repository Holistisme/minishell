/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:01:13 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/23 13:20:38 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

#define FAILURE	-1

static void	set_allocation(void **target, const size_t size);
static void	zero_memory(void *memory, size_t size);
static void	free_memory(t_allocation *last);

/**
 * 🔹 Name: manage_memory
 * ------------------------
 * 📝 Description: saves the last allocation.
 * ↣ Manages memory initialization and freeing.
 * 
 * 📌 Parameters:
 * → const t_action action : the action to be done in the function.
 * → t_allocation *context : if defined, transfers the new last allocation.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: none.
 */
void	manage_memory(const t_action action, t_allocation *context)
{
	static t_allocation	*last = NULL;

	if (action == SET)
	{
		if (!last)
			last = context;
		else
		{
			context->previous = last;
			last = context;
		}
	}
	else if (action == FREE)
		free_memory(last);
}

/**
 * 🔹 Name: set_memory
 * ------------------------
 * 📝 Description: allocates memory for an address and saves it.
 * 
 * 📌 Parameters:
 * → void **target : the address where to allocate memory.
 * → const size_t size : the size of the memory to allocate.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: none.
 */
void	set_memory(void **target, const size_t size)
{
	t_allocation	*new_allocation;

	set_allocation((void **)&new_allocation, sizeof(t_allocation));
	manage_memory(SET, new_allocation);
	set_allocation(target, size);
	new_allocation->memory = *target;
}

/**
 * 🔹 Name: set_allocation
 * ------------------------
 * 📝 Description: allocates memory to a target address.
 * 
 * 📌 Parameters:
 * → void **target : the address where to allocate memory.
 * → const size_t size : the size of the memory to allocate.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: stops the program on allocation failure.
 */
static void	set_allocation(void **target, const size_t size)
{
	*target = NULL;
	if (size)
	{
		*target = malloc(size);
		if (!*target)
			terminate_program(ERR_ALLOC);
		zero_memory(*target, size);
	}
}

/**
 * 🔹 Name: zero_memory
 * ------------------------
 * 📝 Description: resets binary memory to 0.
 * 
 * 📌 Parameters:
 * → void *memory : the memory to be reset.
 * → size_t size : the number of bits to reset.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: none.
 */
static void	zero_memory(void *memory, size_t size)
{
	unsigned char	*bits;

	bits = (unsigned char *)memory;
	while (size > 0)
		bits[size-- - 1] = 0;
}

/**
 * 🔹 Name: free_memory
 * ------------------------
 * 📝 Description: recursively frees each memory allocation since the last one.
 * 
 * 📌 Parameters:
 * → t_allocation *allocation : the memory allocation to be freed currently.
 *
 * 🔄 Return value:
 * ↦ void : no value is returned.
 *
 * ⚠️ Error management: none.
 */
static void	free_memory(t_allocation *allocation)
{
	if (allocation)
	{
		if (allocation->memory)
			free(allocation->memory);
		free_memory(allocation->previous);
		free(allocation);
	}
}
