#include <stdio.h>

#define QUARTER 25
#define DIME 10
#define NICKEL 5
#define PENNY 1

void	count_cash(int *cents, int *coins, int nominal);

int	main(void)
{
	float	cash;
	int		cents;
	int		coins;

	coins = 0;

	do
	{
		printf("Change owed: $");
		scanf("%f", &cash);
	} while (cash < 0);

	cents = (int) (cash * 100);

	count_cash(&cents, &coins, QUARTER);
	count_cash(&cents, &coins, DIME);
	count_cash(&cents, &coins, NICKEL);
	count_cash(&cents, &coins, PENNY);
	
	printf("Total coins: %d\n", coins);
}

void	count_cash(int *cents, int *coins, int nominal)
{
	*coins += *cents / nominal;
	*cents %= nominal;
}
