/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 03:09:01 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 19:34:15 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	is_gap(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	str_len(char *str)
{
	int	count;

	count = 0;
	while (*(str++))
	{
		count++;
	}
	return (count);
}

int	is_radix(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	is_valid(char *str)
{
	int		len;
	int		i;
	int		j;
	char	c;

	len = str_len(str);
	if (len == 0 || len == 1)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		c = str[i];
		j = 0;
		while (str[j] != '\0')
		{
			if (j != i && str[j] == c)
				return (0);
			if ((str[j] == '-' || str[j] == '+') || is_gap(str[j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	result;
	int	operator_type;
	int	len;
	int	temp;

	temp = 0;
	result = 0;
	operator_type = 1;
	len = str_len(base);
	if (!is_valid(base))
		return (0);
	while (is_gap(*str))
		str++;
	while (*str == '-' || *str == '+')
		if (*(str++) == '-')
			operator_type *= -1;
	while (*str)
	{
		temp = is_radix(base, *str);
		if (temp == -1)
			break ;
		result = result * len + temp;
		str++;
	}
	return (result * operator_type);
}
