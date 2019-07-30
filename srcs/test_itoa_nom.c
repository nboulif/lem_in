#include <stdlib.h>

static int		ft_lenstr(long n)
{
	static int nb = 1;
	static int cmp = 1;

	// printf("n -> %ld", n);
	while ((cmp * 10) <= n)
	{
		cmp *= 10;
		nb++;
	}
	// printf("len -> %d\n", nb);
	return (nb);
}

char			*ft_itoa_no_m(char *str, int n)
{
	static int	size = 0;
	static int  last = 1;

	if (n == last + 1 &&
		ft_lenstr(n) == size)
	{
		int ind = size - 1;

		if (str[size - 1] == '9')
		{
			while (str[ind] == '9')
			{
				str[ind] = '0';
				ind--;
			}
			str[ind - 1] += 1;
		}
		else
			str[size - 1] += 1;
        last = n;
		return (str);
	}
	last = n;
	size = ft_lenstr(n);
	str[size] = '\0';
	while (size--)
	{
		str[size] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

int main()
{
    char *str = malloc(15 * sizeof(char));

    str[0] = 'L';
    str[1] = 0;
    for (int i = 1; i < 1000001; i++)
    {
        ft_itoa_no_m(str + 1, i);
        printf("%s\n", str);
    }
    return (0);
}