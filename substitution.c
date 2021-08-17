#include <stdio.h>
#include <ctype.h>
#include <string.h>

int		isvalid (char *key);

void	print_cipher(char *text, char *key);

int	main(int argc, char **argv)
{
	char	text[500];

	if (argc == 2)
	{
		if (!(isvalid(argv[1])))
			return (1);

		printf("plaintext :");
		fgets(text, 500, stdin);
		fflush(stdin);
		printf("ciphertext :");
		print_cipher(text, argv[1]);
	}
	else
	{
		printf("Usage: ./substitution key\n");
		return (1);
	}
	return (0);
}

int	isvalid (char *key)
{
	short	buf[26] = {0};

	if (strlen(key) != 26)
	{
		printf("Key must contain 26 characters.\n");
		return (0);
	}
	for (int i = 0; i < 26; ++i)
	{
		if (!(isalpha(key[i])))
		{
			printf("Key must only contain alphabetic characters.\n");
			return (0);
		}
		if (islower(key[i]))
			key[i] = toupper(key[i]);
		if (buf[key[i] - 'A'] == 1)
		{
			printf("Key must not contain repeated characters.\n");
			return (0);
		}
		else
			buf[key[i] - 'A'] = 1;
	}
	return (1);
}

void	print_cipher(char *text, char *key)
{
	int i = -1;

	while (text[++i] != 0)
		if (isalpha(text[i]))
			if (islower(text[i]))
				putchar(tolower(key[text[i] - 'a']));
			else
				putchar(key[text[i] - 'A']);
		else
			putchar(text[i]);
}
