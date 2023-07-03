/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/06/30 15:17:34 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//EXPORT WITH NO OPTIONS (BUT WITH POTENTIAL ARGUMENTS)
/*Normally, when you run a command at the bash prompt, a dedicated process is
created with its own environment, exclusively for running your command. Any
variables and functions you defined before running the command are not shared
with new processes — unless you explicitly mark them with export.
Example: myvar="This variable is defined." > export myvar > bash > echo $myvar >
"This variable is defined."*/

//check if var is in allowed format (no #, $ or @ in name, starts with letter or _)
int	check_var(void *var)
{
	int		i;
	char	*copy;

	i = 0;
	copy = (char *)var;
	if (((copy[0] > 'Z' && copy[0] < 'a') || copy[0] < 'A'
		|| copy[0] > 'z') && copy[0] != '_')
			return (-1);
	while (copy[i] != '=' && copy[i])
	{
		if (copy[i] == '#' || copy[i] == '@' || copy[i] == '$')
			return (-1);
		i++;
	}
	return (0);
}

//add *var to env tableau
void	add_var_export(void *var, t_env_list **head)
{
	t_env_list	*addback;
	t_env_list	*pre_copy;
	t_env_list	*post_copy;

	if (check_var(var) == -1)
		return (perror("not added\n"));								//include error msg here (bash: export: `=1': not a valid identifier)
	addback = (t_env_list *)malloc(sizeof(t_env_list));
	if (!addback)													//include error msg here
		return ;
	addback->element = ft_strdup(var);
	if (!addback->element)											//include error msg here
		return ;
	pre_copy = get_node(*head, 10);
	post_copy = pre_copy->next;
	pre_copy->next = addback;
	post_copy->prev = addback;
	addback->prev = pre_copy;
	addback->next = post_copy;
}

//cmd: export (without args), prints env in ascii order without the last arg path
void	print_export(t_env_list *env_for_export)
{
	char	**lines;

	//check if last history was "minishell", if yes, add line list_append() with "_="/bin/bash""
	bubble_sort(&env_for_export);
	while (env_for_export)
	{
		lines = ft_split(env_for_export->element, '=');
		if (!lines)
			return ;												//include error msg here
		ft_printf("declare -x %s=%c", lines[0], '"');
		if (lines[1])
			ft_printf("%s", lines[1]);
		ft_printf("%c\n", '"');
		env_for_export = env_for_export->next;
		free(lines[0]);
		free(lines[1]);
		free(lines);
	}
}