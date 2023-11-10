
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ALPHABET_SIZE 26

typedef enum
{
	ENCRYPT = 1,
	DECRYPT
} encrypt_t;

uint8_t* caesarCipher(uint8_t* str, uint8_t key, encrypt_t encryption)
{
	// to make sure that the key is less than 26
	// while (key > ALPHABET_SIZE)
	//{
	//	key -= ALPHABET_SIZE;
	//}
	key = key % ALPHABET_SIZE;

	if (encryption == ENCRYPT)
	{
		for (int i = 0; str[i] != '\0'; i++)
		{
			if ((str[i] >= 'a') && (str[i] <= 'z'))
			{
				// if the the str[i] with the key is greater than 'z' then we need to start from 'a' again
				if (str[i] + key > 'z')
				{
					str[i] = str[i] - (ALPHABET_SIZE - key);
				}
				else
				{
					str[i] = str[i] + key;
				}
			}
			if ((str[i] >= 'A' && str[i] <= 'Z'))
			{
				if (str[i] + key > 'Z')
				{
					str[i] = str[i] - (ALPHABET_SIZE - key);
				}
				else
				{
					str[i] = str[i] + key;
				}
			}
		}
	}
	else if (encryption == DECRYPT)
	{
		for (int i = 0; str[i] != '\0'; i++)
		{
			if ((str[i] >= 'a') && (str[i] <= 'z'))
			{
				if (str[i] - key < 'a')
				{
					str[i] = str[i] + (ALPHABET_SIZE - key);
				}
				else
				{
					str[i] = str[i] - key;
				}
			}
			if ((str[i] >= 'A' && str[i] <= 'Z'))
			{
				if (str[i] - key < 'A')
				{
					str[i] = str[i] + (ALPHABET_SIZE - key);
				}
				else
				{
					str[i] = str[i] - key;
				}
			}
		}
	}
	else
	{
		/* Do nothing */
	}

	return str;
}

int main()
{
	int32_t key, option;

	printf("Enter Key: ");
	scanf("%d", &key);

	printf("Enter Option:\n\t1: ENCRYPT \n\t2: DECRYPT ");
	scanf("%d", &option);

	uint8_t	 str[100];
	uint8_t* encrypted;

	printf("Enter Str: ");
	scanf("%99s", str);

	encrypted = caesarCipher(str, key, option);

	puts(encrypted);
	return 0;
}