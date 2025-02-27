/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overflow_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:29:00 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 18:54:12 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space(int n)
{
	return ((n >= 8 && n <= 13) || n == 32);
}

int	is_operator(char c)
{
	return (c == '+' || c == '-');
}

int	is_num(char n)
{
	return (n >= '0' && n <= '9');
}

int	is_valid_integer(const char *nptr)
{
	int		operator;
	long	result;
	long	max;
	long	min;

	operator = 1;
	result = 0;
	while (is_space(*nptr))
		nptr++;
	if (is_operator(*nptr))
	{
		if (*nptr == '-')
			operator = -1;
		nptr++;
	}
	while (is_num(*nptr))
	{
		result *= 10;
		result += *nptr - '0';
		nptr++;
	}
	result *= operator;
	if (result > 2147483647 || result < -2147483648)
		return (0);
	return (1);
}
