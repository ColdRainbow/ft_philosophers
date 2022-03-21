#include "philosophers.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	int	a;

	a = 0;
	if (num == 0)
		return (0);
	while (num != 0 && str1[a] != '\0' && str2[a] == str1[a])
	{
		num--;
		if (str1[a] == str2[a] && num != 0)
			a++;
	}
	return (((unsigned char *)str1)[a] - ((unsigned char *)str2)[a]);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int				a;
	long long int	b;

	a = 1;
	b = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' || \
					*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		a = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		if (b >= 922337203685477600)
			return (-1);
		if ((b * a) <= -922337203685477)
			return (0);
		b = b * 10 + (*str - 48);
		++str;
	}
	return (b * a);
}

static int	check_char_isalnum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_str_is_int(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 11 || check_char_isalnum(str) == 0)
		return (0);
	if (len == 11)
	{
		if (str[0] == '-')
		{
			if (ft_strncmp(str, MIN_INT, len) > 0)
				return (0);
		}
		else if (str[0] == '+')
		{
			if (ft_strncmp(str, MAX_INT_P, len) > 0)
				return (0);
		}
	}
	else if (len == 10)
	{
		if (ft_strncmp(str, MAX_INT, len) > 0)
			return (0);
	}
	return (1);
}
