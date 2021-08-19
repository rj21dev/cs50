#include <stdio.h>


void	build_pyramid(int n);

int	main(void)
{
	int	n;

	do
	{
		printf("Height (1-8) : ");
		scanf("%d", &n);
	} while (n < 1 || n > 8);
	
	build_pyramid(n);
	return (0);
}

void	build_pyramid(int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			if (j < n - i - 1)
				printf(" ");
			else
				printf("#");
		printf("  ");
		for (int j = 0, m = n - (n - i -1); j < m; ++j)
			printf("#");
		printf("\n");
	}
}