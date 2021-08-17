#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int		isvalid (char *key);

void	print_cipher(char *str, int key);

int	main(int argc, char **argv)
{
	char	text[500];

	if (argc != 2 || !(isvalid(argv[1])))
	{
		printf("Usage: ./caesar key\n");
		return (1);
	}

	printf("plaintext :");
	fgets(text, 500, stdin);
	fflush(stdin);
	printf("ciphertext :");
	print_cipher(text, atoi(argv[1]));
	
	return (0);
}

int	isvalid (char *key)
{
	int	i = -1;

	while (key[++i] != 0)
		if (!(isdigit(key[i])))
			return (0);
	return (1);
}

void	print_cipher(char *str, int key)
{
	int	i = -1;

	while (str[++i] != 0)
		if (isalpha(str[i]))
			if (islower(str[i]))
				putchar('a' + ((str[i] - 'a' + key) % 26));
			else
				putchar('A' + ((str[i] - 'A' + key) % 26));
		else
			putchar(str[i]);
}
