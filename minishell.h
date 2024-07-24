/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:03:26 by aheitz            #+#    #+#             */
/*   Updated: 2024/07/24 13:33:44 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define END_CHARACTER	1
# define NULL_CHARACTER	"\0"
# define PIPE			'|'
# define POSIX_SPACE	" \t\n\v\f\r"

typedef int		t_fd;
typedef char	*t_string;
typedef ssize_t	t_index;

typedef enum e_bool
{
	FALSE	= 0,
	TRUE	= 1
}	t_bool;

typedef enum e_error
{
	ERR_ALLOC	= 0,
}	t_error;

typedef enum e_action
{
	SET		= 0,
	FREE	= 1
}	t_action;

typedef enum e_type
{
	PIPELINE	= 1
}	t_type;

typedef struct s_token
{
	t_type			type;
	t_string		value;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	t_token				*token;
	t_fd				outfile;
	t_string			error;
	struct s_command	*next;
}	t_command;

typedef struct s_token_setup
{
	t_token		*first_token;
	t_token		*current_token;
	t_token		*last_token;
	t_string	inputs;
	char		active_quote;
}	t_token_setup;

typedef struct s_command_setup
{
	t_token		*first_token;
	t_token		*current_token;
	t_command	*first_command;
	t_command	*current_command;
	t_command	*last_command;
	t_fd		pipe_fd[2];
}	t_command_setup;

typedef struct s_allocation
{
	void				*memory;
	struct s_allocation	*previous;
}	t_allocation;

int			main(void);
t_string	get_prompt(void);
void		terminate_program(const t_error error);

void		manage_memory(const t_action action, t_allocation *context);
void		set_memory(void **target, const size_t size);

t_command	*set_commands(t_string inputs);
t_token		*set_tokens(t_string inputs);

t_string	append_string(t_string destination, t_string source);
t_string	append_character(const char character, t_string old_string);
size_t		get_length(const t_string string, const t_string delimiters);
t_bool		is_alphanumeric(const char c);
t_bool		is_inside(const char character, t_string string);
t_bool		is_space(const char c);

#endif