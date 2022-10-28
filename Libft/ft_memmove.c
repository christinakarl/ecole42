/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:58:33 by ckarl             #+#    #+#             */
/*   Updated: 2022/10/28 14:27:25 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	size_t			i;
	char			*s2;
	char			*s1;

	s1 = (char *)str1;
	s2 = (char *)str2;
	i = 0;
	if (str2 < str1)
	{
		while (n > 0)
		{
			s1[n] = s2[n];
			n--;
		}
	}
	else
	{	
		while (i < n)
		{
			s1[i] = s2[i];
			i++;
		}
	}
	return (str1);
}
