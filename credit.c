#include <stdio.h>

int	is_amex(long number, int length);

int	is_mastercard(long number, int length);

int	is_visa(long number, int length);

int	check_sum(long number, int *i);

int	main(void)
{
	long	number;
	int		length;
	int		sum;

	do
	{
		printf("Number: "); //Only digits. No chars. Pizdets will come...
		scanf("%li", &number);
	} while (number <= 0);

	length = 0;
	sum = check_sum(number, &length);
	
	if (sum % 10 == 0)
	{
		if(is_amex(number, length))
			printf("AMEX\n");
		if(is_mastercard(number, length))
			printf("MASTERCARD\n");
		if(is_visa(number, length))
			printf("VISA\n");
	}
	else
		printf("INVALID\n");
}

int	check_sum(long number, int *i)
{
	int	tmp;
	int sum;
	
	sum = 0;
	while (number != 0)
	{
		if (*i % 2 != 0)
		{
			tmp = 2 * (number % 10);
			if (tmp > 9)
				sum += (tmp % 10 + tmp / 10);
			else
				sum += tmp;
		}
		else
			sum += number % 10;
		number /= 10;
		++(*i);
	}
	return (sum);
}

int	is_amex(long number, int length)
{
	long id = number / 10000000000000;
	return ((id == 34 || id == 37) && length == 15);
}

int	is_mastercard(long number, int length)
{
	long id = number / 100000000000000;
	return ((id >= 51 && id <= 55) && length == 16);
}

int	is_visa(long number, int length)
{
	long id = number / 1000000000000;
	long id2 = number / 1000000000000000;
	return ((id == 4 && length == 13) || (id2 == 4 && length == 16));
}
