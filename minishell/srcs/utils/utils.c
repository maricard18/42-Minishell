/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipa <filipa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:42:53 by filipa            #+#    #+#             */
/*   Updated: 2023/05/10 19:13:34 by filipa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history_node	*ft_lstnew_2(void *content)
{
	struct s_history_node	*new;

	new = (struct s_history_node *)malloc(sizeof(struct s_history_node));
	ft_memset(new, 0, sizeof(t_history_node));
	if (new)
		new->content = content;
	new->previous = NULL;
	return (new);
}

void	free_data(t_minishell_state *data, int exit_code)
{
	free_env(data->environment_variables);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	exit(exit_code);
}