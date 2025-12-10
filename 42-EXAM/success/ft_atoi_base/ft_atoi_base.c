int		ft_atoi_base(const char *str, int str_base)
{
	int		i;
	int		sign;
	int		value;
	int		res;
	char	c;

	if (str_base < 2 || str_base > 16)
		return (0);

	i = 0;
	sign = 1;
	res = 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}

	while (str[i])
	{
		c = str[i];

		/* converti carattere in valore numerico */
		if (c >= '0' && c <= '9')
			value = c - '0';
		else if (c >= 'a' && c <= 'f')
			value = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			value = c - 'A' + 10;
		else
			break;

		/* se la cifra è fuori dalla base → stop */
		if (value >= str_base)
			break;

		res = res * str_base + value;
		i++;
	}
	return (res * sign);
}

/* 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Uso: %s <stringa> <base>\n", argv[0]);
        return 1;
    }

    int base = atoi(argv[2]);
    int result = ft_atoi_base(argv[1], base);

    printf("Risultato: %d\n", result);

    return 0;
}
 */